#include <jxl/decode.h>
#include <jxl/encode.h>
#include <jxl/thread_parallel_runner.h>

#include "import_jxl.h"

#include <climits>
#include <stdio.h>
#include <thread>

#include "logs.h"

static bool load_jxl_from_memory(const uint8_t *data, size_t size, uint32_t *out_width, uint32_t *out_height, uint16_t **out_pixels)
{
    if (!data || !size || !out_width || !out_height || !out_pixels) {
        LOGE("load_jxl_from_memory called with wrong parameters");
        return false;
    }
    *out_width = 0;
    *out_height = 0;
    *out_pixels = nullptr;

    JxlSignature signature = JxlSignatureCheck(data, size);
    if (signature != JXL_SIG_CODESTREAM && signature != JXL_SIG_CONTAINER) {
        LOGE("Not a valid JPEG XL");
        return false;
    }

    JxlDecoder *decoder = JxlDecoderCreate(nullptr);
    if (!decoder) {
        LOGE("ERROR: JxlDecoderCreate failed");
        return false;
    }

    int maxThreads = std::thread::hardware_concurrency();
    if (maxThreads > 16) {
        maxThreads = 16;
    } else if (maxThreads < 1) {
        maxThreads = 1;
    }

    void *runner = nullptr;
    if (maxThreads > 1) {
        runner = JxlThreadParallelRunnerCreate(nullptr, maxThreads);
        if (JxlDecoderSetParallelRunner(decoder, JxlThreadParallelRunner, runner) != JXL_DEC_SUCCESS) {
            LOGE("ERROR: JxlDecoderSetParallelRunner failed");
            JxlThreadParallelRunnerDestroy(runner);
            JxlDecoderDestroy(decoder);
            return false;
        }
    }

    if (JxlDecoderSetInput(decoder, data, size) != JXL_DEC_SUCCESS) {
        LOGE("ERROR: JxlDecoderSetInput failed");
        if (runner) {
            JxlThreadParallelRunnerDestroy(runner);
        }
        JxlDecoderDestroy(decoder);
        return false;
    }

    JxlDecoderCloseInput(decoder);

    JxlDecoderStatus status = JxlDecoderSubscribeEvents(decoder, JXL_DEC_BASIC_INFO | JXL_DEC_COLOR_ENCODING | JXL_DEC_FULL_IMAGE);
    if (status == JXL_DEC_ERROR) {
        LOGE("ERROR: JxlDecoderSubscribeEvents failed");
        if (runner) {
            JxlThreadParallelRunnerDestroy(runner);
        }
        JxlDecoderDestroy(decoder);
        return false;
    }

    status = JxlDecoderProcessInput(decoder);
    if (status == JXL_DEC_ERROR) {
        LOGE("ERROR: JXL decoding failed");
        if (runner) {
            JxlThreadParallelRunnerDestroy(runner);
        }
        JxlDecoderDestroy(decoder);
        return false;
    }
    if (status == JXL_DEC_NEED_MORE_INPUT) {
        LOGE("ERROR: JXL data incomplete");
        if (runner) {
            JxlThreadParallelRunnerDestroy(runner);
        }
        JxlDecoderDestroy(decoder);
        return false;
    }

    JxlBasicInfo basicinfo;

    status = JxlDecoderGetBasicInfo(decoder, &basicinfo);
    if (status != JXL_DEC_SUCCESS) {
        LOGE("ERROR: JXL basic info not available");
        if (runner) {
            JxlThreadParallelRunnerDestroy(runner);
        }
        JxlDecoderDestroy(decoder);
        return false;
    }

    status = JxlDecoderProcessInput(decoder);
    if (status != JXL_DEC_COLOR_ENCODING) {
        LOGE("Unexpected event %d instead of JXL_DEC_COLOR_ENCODING", status);
        if (runner) {
            JxlThreadParallelRunnerDestroy(runner);
        }
        JxlDecoderDestroy(decoder);
        return false;
    }

    if (basicinfo.uses_original_profile == JXL_FALSE) {
        JxlColorEncoding preferred_color_encoding;
        JxlColorEncodingSetToSRGB(&preferred_color_encoding, JXL_FALSE);
        JxlDecoderSetPreferredColorProfile(decoder, &preferred_color_encoding);
    }

    status = JxlDecoderProcessInput(decoder);
    if (status != JXL_DEC_NEED_IMAGE_OUT_BUFFER) {
        LOGE("Unexpected event %d instead of JXL_DEC_NEED_IMAGE_OUT_BUFFER", status);
        if (runner) {
            JxlThreadParallelRunnerDestroy(runner);
        }
        JxlDecoderDestroy(decoder);
        return false;
    }

    JxlPixelFormat pixel_format;
    pixel_format.num_channels = 3;
    pixel_format.data_type = JXL_TYPE_UINT16;
    pixel_format.endianness = JXL_NATIVE_ENDIAN;
    pixel_format.align = 0;

    const size_t n_entries = size_t(3) * basicinfo.xsize * basicinfo.ysize;
    const size_t output_buffer_size = n_entries * 2;
    uint16_t *buffer = new uint16_t[n_entries];

    if (JxlDecoderSetImageOutBuffer(decoder, &pixel_format, buffer, output_buffer_size) != JXL_DEC_SUCCESS) {
        LOGE("ERROR: JxlDecoderSetImageOutBuffer failed");
        delete[] buffer;
        if (runner) {
            JxlThreadParallelRunnerDestroy(runner);
        }
        JxlDecoderDestroy(decoder);
        return false;
    }

    status = JxlDecoderProcessInput(decoder);
    if (status != JXL_DEC_FULL_IMAGE) {
        LOGE("Unexpected event %d instead of JXL_DEC_FULL_IMAGE", status);
        delete[] buffer;
        if (runner) {
            JxlThreadParallelRunnerDestroy(runner);
        }
        JxlDecoderDestroy(decoder);
        return false;
    }

    if (runner) {
        JxlThreadParallelRunnerDestroy(runner);
    }
    JxlDecoderDestroy(decoder);

    *out_pixels = buffer;
    *out_width = basicinfo.xsize;
    *out_height = basicinfo.ysize;
    return true;
}

bool load_jxl_from_file(const char *filename, uint32_t *out_width, uint32_t *out_height, uint16_t **out_pixels)
{
    if (!filename || !out_width || !out_height || !out_pixels) {
        LOGE("load_jxl_from_file called with wrong parameters");
        return false;
    }

    *out_width = 0;
    *out_height = 0;
    *out_pixels = nullptr;

    FILE *file = fopen(filename, "rb");
    if (!file) {
        LOGE("Failed to open %s", filename);
        return false;
    }

    if (fseek(file, 0, SEEK_END) != 0) {
        fclose(file);
        return false;
    }

    long size = ftell(file);
    if (size >= LONG_MAX || size <= 0) {
        fclose(file);
        return false;
    }

    if (fseek(file, 0, SEEK_SET) != 0) {
        fclose(file);
        return false;
    }

    uint8_t *file_content = new uint8_t[size];
    size_t readsize = fread(file_content, 1, size, file);

    fclose(file);

    if (readsize != static_cast<size_t>(size)) {
        LOGE("Failed to read data from %s", filename);
        return false;
    }

    if (load_jxl_from_memory(file_content, readsize, out_width, out_height, out_pixels)) {
        delete[] file_content;
        return true;
    }

    delete[] file_content;
    LOGE("Falied to decode %s as JXL", filename);
    return false;
}
