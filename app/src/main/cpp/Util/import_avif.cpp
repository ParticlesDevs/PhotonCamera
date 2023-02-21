#include "import_avif.h"
#include <avif/avif.h>

#include <stdio.h>
#include <thread>

#include "logs.h"

bool load_avif_from_file(const char *filename, uint32_t *out_width, uint32_t *out_height, uint16_t **out_pixels)
{
    if (!filename || !out_width || !out_height || !out_pixels) {
        LOGE("load_avif_from_file called with wrong parameters");
        return false;
    }

    *out_width = 0;
    *out_height = 0;
    *out_pixels = nullptr;

    avifDecoder *decoder = avifDecoderCreate();

    int maxThreads = std::thread::hardware_concurrency();
    if (maxThreads > 16) {
        maxThreads = 16;
    } else if (maxThreads < 1) {
        maxThreads = 1;
    }
    decoder->maxThreads = maxThreads;

    avifResult decodeResult = avifDecoderSetIOFile(decoder, filename);
    if (decodeResult != AVIF_RESULT_OK) {
        LOGE("avifDecoderSetIOFile failed for file %s: %s", filename, avifResultToString(decodeResult));
        avifDecoderDestroy(decoder);
        return false;
    }

    decodeResult = avifDecoderParse(decoder);
    if (decodeResult != AVIF_RESULT_OK) {
        LOGE("avifDecoderParse failed for file %s: %s", filename, avifResultToString(decodeResult));
        avifDecoderDestroy(decoder);
        return false;
    }

    decodeResult = avifDecoderNextImage(decoder);
    if (decodeResult != AVIF_RESULT_OK) {
        LOGE("avifDecoderNextImage failed for file %s: %s", filename, avifResultToString(decodeResult));
        avifDecoderDestroy(decoder);
        return false;
    }

    const size_t n_entries = size_t(3) * decoder->image->width * decoder->image->height;
    uint16_t *buffer = new uint16_t[n_entries];
    avifRGBImage rgb;

    avifRGBImageSetDefaults(&rgb, decoder->image);
    rgb.depth = 16;
    rgb.format = AVIF_RGB_FORMAT_RGB;
    rgb.rowBytes = 6 * decoder->image->width;
    rgb.pixels = reinterpret_cast<uint8_t *>(buffer);

    decodeResult = avifImageYUVToRGB(decoder->image, &rgb);
    if (decodeResult != AVIF_RESULT_OK) {
        LOGE("avifImageYUVToRGB failed for file %s: %s", filename, avifResultToString(decodeResult));
        delete[] buffer;
        avifDecoderDestroy(decoder);
        return false;
    }

    *out_pixels = buffer;
    *out_width = decoder->image->width;
    *out_height = decoder->image->height;
    avifDecoderDestroy(decoder);
    return true;
}
