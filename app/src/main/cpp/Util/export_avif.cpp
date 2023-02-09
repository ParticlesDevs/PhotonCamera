
#include "export_avif.h"
#include <avif/avif.h>

#include <thread>

#include <stdio.h>
#define LOGE printf

bool save_avif_to_file(const char *filename, uint32_t width, uint32_t height, const uint16_t *pixels, const uint8_t *exif, size_t exifSize)
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

    avifResult res;
    avifImage *avif = avifImageCreate(width, height, 10, AVIF_PIXEL_FORMAT_YUV444);

    avif->colorPrimaries = AVIF_COLOR_PRIMARIES_BT709;
    avif->transferCharacteristics = AVIF_TRANSFER_CHARACTERISTICS_SRGB;
    avif->matrixCoefficients = AVIF_MATRIX_COEFFICIENTS_BT709;

    if (save_exif) {
        avifImageSetMetadataExif(avif, exif, exifSize);
    }

    avifRGBImage rgb;
    avifRGBImageSetDefaults(&rgb, avif);

    rgb.depth = 16;
    rgb.format = AVIF_RGB_FORMAT_RGB;
    rgb.rowBytes = width * 6;
    rgb.pixels = reinterpret_cast<uint8_t *>(const_cast<uint16_t *>(pixels));

    res = avifImageRGBToYUV(avif, &rgb);
    if (res != AVIF_RESULT_OK) {
        LOGE("ERROR in avifImageRGBToYUV: %s\n", avifResultToString(res));
        avifImageDestroy(avif);
        return false;
    }

    avifRWData raw = AVIF_DATA_EMPTY;
    avifEncoder *encoder = avifEncoderCreate();

    int maxThreads = std::thread::hardware_concurrency();
    if (maxThreads > 16) {
        maxThreads = 16;
    } else if (maxThreads < 1) {
        maxThreads = 1;
    }
    encoder->maxThreads = maxThreads;
    encoder->minQuantizer = 5;
    encoder->maxQuantizer = 25;
    encoder->autoTiling = AVIF_TRUE;
    encoder->speed = 6;

    res = avifEncoderWrite(encoder, avif, &raw);
    avifEncoderDestroy(encoder);
    avifImageDestroy(avif);

    if (res == AVIF_RESULT_OK) {
        bool success;
        FILE *file = fopen(filename, "wb");
        if (!file) {
            LOGE("ERROR: unable to save %s\n", filename);
            success = false;
        } else {
            size_t byteswritten = fwrite(raw.data, 1, raw.size, file);
            fclose(file);
            if (byteswritten == raw.size) {
                success = true;
            } else {
                LOGE("ERROR: Unable to write to %s\n", filename);
                success = false;
            }
        }
        avifRWDataFree(&raw);
        return success;
    } else {
        LOGE("ERROR: Failed to encode: %s\n", avifResultToString(res));
    }
    return false;
}
