#include "export_jxl.h"
#include <jxl/encode.h>
#include <jxl/thread_parallel_runner.h>

#include <string.h>
#include <thread>
#include <vector>

#include <stdio.h>
#define LOGE printf

bool save_jxl_to_file(const char *filename, uint32_t width, uint32_t height, const uint16_t *pixels, const uint8_t *exif, size_t exifSize)
{
    if (!filename || width == 0 || height == 0 || !pixels) {
        LOGE("ERROR: save_avif_to_file called with invalid parameters!\n");
        return false;
    }
    bool save_exif = false;

    if (exif && exifSize > 4) {
        const uint8_t tiffHeaderBE[4] = {'M', 'M', 0, 42};
        const uint8_t tiffHeaderLE[4] = {'I', 'I', 42, 0};

        while (exifSize > 4) {
            if ((exif[0] == tiffHeaderBE[0] && exif[1] == tiffHeaderBE[1] && exif[2] == tiffHeaderBE[2] && exif[3] == tiffHeaderBE[3])
                || (exif[0] == tiffHeaderLE[0] && exif[1] == tiffHeaderLE[1] && exif[2] == tiffHeaderLE[2] && exif[3] == tiffHeaderLE[3])) {
                save_exif = true;
                break;
            }
            exifSize--;
            exif++;
        }
    }

    JxlEncoder *encoder = JxlEncoderCreate(nullptr);
    if (!encoder) {
        LOGE("Failed to create Jxl encoder\n");
        return false;
    }

    JxlBasicInfo output_info;
    JxlEncoderInitBasicInfo(&output_info);

    output_info.uses_original_profile = JXL_FALSE;
    output_info.have_container = JXL_TRUE;
    output_info.orientation = JXL_ORIENT_IDENTITY;
    output_info.num_color_channels = 3;
    output_info.bits_per_sample = 16;
    output_info.alpha_bits = 0;
    output_info.xsize = width;
    output_info.ysize = height;

    JxlPixelFormat pixel_format;
    pixel_format.endianness = JXL_NATIVE_ENDIAN;
    pixel_format.align = 0;
    pixel_format.data_type = JXL_TYPE_UINT16;
    pixel_format.num_channels = 3;

    JxlColorEncoding color_profile;
    JxlColorEncodingSetToSRGB(&color_profile, JXL_FALSE);

    JxlEncoderStatus status;

    JxlEncoderUseContainer(encoder, JXL_TRUE);
    if (save_exif) {
        JxlEncoderUseBoxes(encoder);
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
        status = JxlEncoderSetParallelRunner(encoder, JxlThreadParallelRunner, runner);
        if (status != JXL_ENC_SUCCESS) {
            LOGE("JxlEncoderSetParallelRunner failed\n");
            JxlThreadParallelRunnerDestroy(runner);
            JxlEncoderDestroy(encoder);
            return false;
        }
    }

    status = JxlEncoderSetBasicInfo(encoder, &output_info);
    if (status != JXL_ENC_SUCCESS) {
        LOGE("JxlEncoderSetBasicInfo failed!\n");
        JxlThreadParallelRunnerDestroy(runner);
        if (runner) {
            JxlEncoderDestroy(encoder);
        }
        return false;
    }

    status = JxlEncoderSetColorEncoding(encoder, &color_profile);
    if (status != JXL_ENC_SUCCESS) {
        LOGE("JxlEncoderSetColorEncoding failed!\n");
        JxlThreadParallelRunnerDestroy(runner);
        if (runner) {
            JxlEncoderDestroy(encoder);
        }
        return false;
    }

    JxlEncoderFrameSettings *encoder_options = JxlEncoderFrameSettingsCreate(encoder, nullptr);
    JxlEncoderSetFrameDistance(encoder_options, 1.0f);
    JxlEncoderSetFrameLossless(encoder_options, JXL_FALSE);

    const size_t buffer_size = size_t(6) * height * width;
    status = JxlEncoderAddImageFrame(encoder_options, &pixel_format, pixels, buffer_size);
    if (status == JXL_ENC_ERROR) {
        LOGE("JxlEncoderAddImageFrame failed!\n");
        if (runner) {
            JxlThreadParallelRunnerDestroy(runner);
        }
        JxlEncoderDestroy(encoder);
        return false;
    }

    if (save_exif) {
        const JxlBoxType exif_box_type = {'E', 'x', 'i', 'f'};
        uint8_t *box_content = new uint8_t[4 + exifSize];

        box_content[0] = 0;
        box_content[1] = 0;
        box_content[2] = 0;
        box_content[3] = 0;
        memcpy(box_content + 4, exif, exifSize);

        status = JxlEncoderAddBox(encoder, exif_box_type, box_content, 4 + exifSize, JXL_FALSE);
        if (status != JXL_ENC_SUCCESS) {
            LOGE("Failed to save metadata box\n");
        }
        delete[] box_content;
    }

    JxlEncoderCloseInput(encoder);

    std::vector<uint8_t> compressed;

    compressed.resize(4096);
    uint8_t *next_out = compressed.data();
    size_t avail_out = compressed.size() - (next_out - compressed.data());
    status = JXL_ENC_NEED_MORE_OUTPUT;
    while (status == JXL_ENC_NEED_MORE_OUTPUT) {
        status = JxlEncoderProcessOutput(encoder, &next_out, &avail_out);
        if (status == JXL_ENC_NEED_MORE_OUTPUT) {
            size_t offset = next_out - compressed.data();
            compressed.resize(compressed.size() * 2);
            next_out = compressed.data() + offset;
            avail_out = compressed.size() - offset;
        }
    }
    compressed.resize(next_out - compressed.data());

    if (runner) {
        JxlThreadParallelRunnerDestroy(runner);
    }
    JxlEncoderDestroy(encoder);

    if (status != JXL_ENC_SUCCESS) {
        LOGE("JxlEncoderProcessOutput failed\n");
        return false;
    }

    if (compressed.size() == 0) {
        LOGE("No data in output\n");
        return false;
    }

    FILE *file = fopen(filename, "wb");
    if (!file) {
        LOGE("ERROR: unable to save %s\n", filename);
        return false;
    }

    size_t byteswritten = fwrite(compressed.data(), 1, compressed.size(), file);
    fclose(file);

    if (byteswritten != compressed.size()) {
        LOGE("ERROR: Unable to write to %s\n", filename);
        return false;
    }

    return true;
}
