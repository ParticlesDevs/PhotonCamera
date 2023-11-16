//
// Created by eszdman on 30.12.2022.
//

#ifndef PHOTONCAMERA_CAMERAPARAMETERS_H
#define PHOTONCAMERA_CAMERAPARAMETERS_H
#include <utility>
#include <vector>
#include <regex>
#include "ProcessingParameters.h"
#include "gl.h"
//Camera control and info structures
enum Backend { CameraNDK, Camera2API };
struct SensorParameters{
    const char* id; //Camera id string
    int rawFormat;
    int selectedPreview; // Selected preview size
    int selectedRaw; // Selected raw size

    ProcessingParameters processing;
    std::vector<std::pair<int,int>> previewSizes; // Sensor YUV sizes
    std::vector<std::string> previewNames; // Sensor YUV formatted names
    std::vector<std::pair<int,int>> rawSizes; // Sensor RAW10 RAW12 RAW16 sizes
    std::vector<std::string> rawNames; // Sensor RAW10 RAW12 RAW16 formatted names
};
struct CameraParameters{
    Backend currentBackend = CameraNDK;
    GLuint cameraPreviewID;
    std::pair<int, int> previewSize;
    std::pair<int, int> rawSize;
    int rawFormat;
    int selectedPreview; // Selected preview size
    int selectedRaw; // Selected raw size
    SensorParameters *currentSensor;



    int selectedID; //Camera id number
    const char* id; //Camera id string
    std::vector<std::string> cameraIDs;
    std::vector<SensorParameters> sensors;


    bool previewActive = false;
    bool takePicture = false; // Button to take picture from camera
    bool resetResCamera = false;
    bool flipCamera = false;
    float aspect = 1.f;
    int buffCnt = 0;
    int buffAvailable = 50;
    int requestedBuffers = 0;
    int maxRequest = 5;
};
#endif //PHOTONCAMERA_CAMERAPARAMETERS_H
