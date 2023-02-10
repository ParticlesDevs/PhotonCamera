//
// Created by eszdman on 05.01.2023.
//

#ifndef PHOTONCAMERA_PROCESSINGPARAMETERS_H
#define PHOTONCAMERA_PROCESSINGPARAMETERS_H
#include <utility>
#include <glm/glm.hpp>
using namespace glm;
struct ProcessingParameters{
    //Characteristics
    char CFA;
    int analogISO;
    int whiteLevel = 1023;
    int processedWL = -1;
    int referenceIlluminant1;
    int referenceIlluminant2;
    int cameraRotation;
    u16vec2 rawSize;
    u16vec4 sensorRect;
    f32vec2 sensorSize;
    float aperture;
    float sensorSensitivity;
    float proPhotoToSRGB[9];
    float sensorToProPhoto[9];
    float calibrationTransform1[9];
    float calibrationTransform2[9];
    float colorSpaceTransform1[9];
    float colorSpaceTransform2[9];
    float forwardMatrix1[9];
    float forwardMatrix2[9];
    float focalLength;

    //CaptureResult
    bool dynamicBL;
    bool gainMapUsage;
    float blackLevel[4];
    float whitePoint[3];
    u16vec2 mapSize;
    float* gainMap;
};
#endif //PHOTON