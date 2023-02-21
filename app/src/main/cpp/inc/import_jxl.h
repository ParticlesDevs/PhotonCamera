#ifndef PHOTONCAMERA_IMPORT_JXL_H
#define PHOTONCAMERA_IMPORT_JXL_H

#include <stddef.h>
#include <stdint.h>

bool load_jxl_from_file(const char *filename, uint32_t *out_width, uint32_t *out_height, uint16_t **out_pixels);

#endif // PHOTONCAMERA_IMPORT_JXL_H
