//
// Created by eszdman on 30.12.2022.
//

#ifndef PHOTONCAMERA_CAMERAPARAMETERS_H
#define PHOTONCAMERA_CAMERAPARAMETERS_H
#include <utility>
#include <vector>
enum Backend { CameraNDK, Camera2API };
struct CameraParameters{
    Backend currentBackend = CameraNDK;
    GLuint cameraPreviewID;
    const char* id; //Camera id string
    std::pair<int, int> previewSize;
    std::pair<int, int> rawSize;
    int selectedPreview; // Selected preview size
    int selectedRaw; // Selected raw size
    int rawFormat;

    std::vector<std::pair<int,int>> previewSizes; // Camera YUV sizes
    std::vector<std::string> previewNames; // Camera YUV formatted names
    std::vector<std::pair<int,int>> rawSizes; // Camera RAW10 RAW12 RAW16 sizes
    std::vector<std::string> rawNames; // Camera RAW10 RAW12 RAW16 formatted names

    bool takePicture = false; // Button to take picture from camera
    bool resetResCamera = false;
    float aspect = 1.f;
    int buffCnt = 0;
    int buffAvailable = 50;
    int requestedBuffers = 0;
    int maxRequest = 50;
};
#endif //PHOTONCAMERA_CAMERAPARAMETERS_H
