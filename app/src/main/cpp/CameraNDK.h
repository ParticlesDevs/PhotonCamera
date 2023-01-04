//
// Created by eszdman on 27.10.2022.
//

#ifndef PHOTONCAMERA_CAMERANDK_H
#define PHOTONCAMERA_CAMERANDK_H
#include <camera/NdkCameraDevice.h>
#include <camera/NdkCameraManager.h>
#include <camera/NdkCameraMetadata.h>
#include <camera/NdkCameraMetadataTags.h>
#include <media/NdkImageReader.h>
#include <logs.h>
#include <GLES3/gl3.h>
#include <android/native_window_jni.h>
#include <utility>
#include <vector>
#include "CameraParameters.h"

#define MAXFRAMES 51
static std::vector<AImage*> buffers;
class CameraNDK {
public:
    CameraParameters *parameters;
    ACameraDevice_request_template templateID;
    //int32_t tagsEntries;
    //const uint32_t* tags;
    ACameraMetadata *cameraCharacteristics;
    ANativeWindow *theNativeWindow;
    ANativeWindow *readerNativeWindow;
    ACameraDevice *cameraDevice;
    ACaptureRequest *captureRequest;
    ACameraOutputTarget *cameraOutputTarget;
    ACameraOutputTarget *OutputTarget;
    ACaptureSessionOutput *sessionOutput;
    ACaptureSessionOutput *readerOutput;
    ACaptureSessionOutputContainer *captureSessionOutputContainer;
    ACameraCaptureSession *captureSession;
    AImageReader *inputFrames;

    ACameraDevice_StateCallbacks deviceStateCallbacks;
    ACameraCaptureSession_stateCallbacks captureSessionStateCallbacks;
    ACameraCaptureSession_captureCallbacks captureSessionCaptureCallbacks;
    void OpenCamera(ACameraDevice_request_template templateId,AIMAGE_FORMATS format, float currentAspect);
    void CloseCamera();
    void StartPreview();
    void MainSize(AIMAGE_FORMATS format, float currentAspect = -1.f) const;
    void PreviewSize() const;

    void Reset();

    void Restart();
};


#endif //PHOTONCAMERA_CAMERANDK_H
