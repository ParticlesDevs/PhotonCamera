#include "exiv_wrapper.h"

#include "logs.h"

bool prerare_exif_blob(Exiv2::Blob &blob, uint32_t width, uint32_t height)
{
    try {
        Exiv2::ExifData exif_data;
        exif_data["Exif.Photo.PixelXDimension"] = width;
        exif_data["Exif.Image.ImageWidth"] = width;
        exif_data["Exif.Photo.PixelYDimension"] = height;
        exif_data["Exif.Image.ImageLength"] = height;
        exif_data["Exif.Image.Software"] = "PhotonCamera-" VERSION_NAME VERSION_BUILD;

        Exiv2::ExifParser::encode(blob, Exiv2::littleEndian, exif_data);

    } catch (Exiv2::Error &e) {
        LOGE("EXIV2 error: %d %s", e.code(), e.what());
        return false;
    }

    return (blob.size() > 0) ? true : false;
}
