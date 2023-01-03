//
// Created by eszdman on 07.11.2022.
//

#ifndef PHOTONCAMERA_FILEMANAGER_H
#define PHOTONCAMERA_FILEMANAGER_H
#include <string>
#include <sys/stat.h>
#include <media/NdkImageReader.h>
#include <cstdlib>
#include <dirent.h>
#include <ctime>
#include <vector>
#include <filesystem>
#include "logs.h"

#define EXTERNAL_DIR "//sdcard//"
#define DCIM_CAMERA "//DCIM//CameraNDK//"
#define PHOTON_TUNING_DIR //DCIM//PhotonCamera//Tuning//

std::vector<std::string> getAllImageFiles();
void CreateDirs();
void WriteFile(AImage* image);

#endif //PHOTONCAMERA_FILEMANAGER_H
