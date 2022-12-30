//
// Created by eszdman on 30.12.2022.
//

#ifndef PHOTONCAMERA_CAMERAPARAMETERS_H
#define PHOTONCAMERA_CAMERAPARAMETERS_H
#include <utility>
struct CameraParameters{
    std::pair<int, int> previewSize;
    std::pair<int, int> rawSize;
    bool takePicture = false;
    float aspect = 1.f;
    int buffCnt = 50;
    int buffAvailable = 50;
    int requestedBuffers = 0;
    int maxRequest = 50;
};
#endif //PHOTONCAMERA_CAMERAPARAMETERS_H
