#ifndef PHOTONCAMERA_EXIV_WRAPPER
#define PHOTONCAMERA_EXIV_WRAPPER

#include <exiv2/exiv2.hpp>

bool prerare_exif_blob(Exiv2::Blob &blob, uint32_t width, uint32_t height);

#endif // PHOTONCAMERA_EXIV_WRAPPER
