//
// Created by eszdman on 27.10.2022.
//

#ifndef PHOTONCAMERA_LOGS_H
#define PHOTONCAMERA_LOGS_H
#include <android/log.h>

#define  LOG_TAG    "PhotonCamera Native"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)

#endif //PHOTONCAMERA_LOGS_H
