#ifndef PHOTONCAMERA_EXPORT_JXL_H
#define PHOTONCAMERA_EXPORT_JXL_H

#include <stddef.h>
#include <stdint.h>

bool save_jxl_to_file(const char *filename, uint32_t width, uint32_t height, const uint16_t *pixels, const uint8_t *exif, size_t exifSize);

#endif // PHOTONCAMERA_EXPORT_JXL_H
