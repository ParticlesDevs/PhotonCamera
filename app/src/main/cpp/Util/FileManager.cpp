//
// Created by eszdman on 07.11.2022.
//
#include <FileManager.h>
static const char *kDirName = "/sdcard/DCIM/Camera/";
static const char *kFileName = "capture";
namespace fs = std::__fs::filesystem;
void mkdr(const char* _path){
    DIR *dir = opendir(_path);
    if (dir) {
        closedir(dir);
    } else {
        std::string cmd = "mkdir -p ";
        cmd += kDirName;
        system(cmd.c_str());
    }
}
std::vector<std::string> getAllImageFiles(){
    for (const auto & entry : fs::directory_iterator(kDirName)){
        //std::cout << entry.path() << std::endl;
        LOGD(" file: %s",entry.path().c_str());
    }
    return {};
}
void CreateDirs(){
    int    result;
    //result = mkdir(EXTERNAL_DIR DCIM_CAMERA, 0700);
    //result = mkdir(EXTERNAL_DIR PHOTON_TUNING_DIR, 0700);
    mkdr(EXTERNAL_DIR DCIM_CAMERA);
    mkdr(EXTERNAL_DIR PHOTON_TUNING_DIR);
}
void WriteFile(AImage* image){
    int planeCount;
    media_status_t status = AImage_getNumberOfPlanes(image, &planeCount);
    uint8_t *data = nullptr;
    int len = 0;
    AImage_getPlaneData(image, 0, &data, &len);

    DIR *dir = opendir(kDirName);
    if (dir) {
        closedir(dir);
    } else {
        std::string cmd = "mkdir -p ";
        cmd += kDirName;
        system(cmd.c_str());
    }

    struct timespec ts {
            0, 0
    };
    clock_gettime(CLOCK_REALTIME, &ts);
    struct tm localTime{};
    localtime_r(&ts.tv_sec, &localTime);

    std::string fileName = kDirName;
    std::string dash("-");
    fileName += kFileName + std::to_string(localTime.tm_mon) +
                std::to_string(localTime.tm_mday) + dash +
                std::to_string(localTime.tm_hour) +
                std::to_string(localTime.tm_min) +
                std::to_string(localTime.tm_sec) + ".jpg";
    FILE *file = fopen(fileName.c_str(), "wb");
    if (file && data && len) {
        fwrite(data, 1, len, file);
        fclose(file);
    } else {
        if (file)
            fclose(file);
    }
    AImage_delete(image);
}