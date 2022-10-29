//
// Created by eszdman on 27.10.2022.
//

#ifndef PHOTONCAMERA_CAMERA_H
#define PHOTONCAMERA_CAMERA_H
#include <camera/NdkCameraDevice.h>
#include <camera/NdkCameraManager.h>
#include <camera/NdkCameraMetadata.h>
#include <camera/NdkCameraMetadataTags.h>
#include <media/NdkImageReader.h>
#include <logs.h>
#include <GLES3/gl3.h>
#include <android/native_window_jni.h>
#include <utility>
class Camera {
public:
    GLuint texID;
    int32_t tagsEntries;
    const uint32_t* tags;
    ACameraMetadata *cameraCharacteristics;

    ANativeWindow *theNativeWindow;
    ACameraDevice *cameraDevice;
    ACaptureRequest *captureRequest;
    ACameraOutputTarget *cameraOutputTarget;
    ACaptureSessionOutput *sessionOutput;
    ACaptureSessionOutputContainer *captureSessionOutputContainer;
    ACameraCaptureSession *captureSession;

    ACameraDevice_StateCallbacks deviceStateCallbacks;
    ACameraCaptureSession_stateCallbacks captureSessionStateCallbacks;
    ACameraCaptureSession_captureCallbacks captureSessionCaptureCallbacks;
    void OpenCamera(ACameraDevice_request_template templateId);
    void CloseCamera();
    void StartPreview();
    std::pair<int,int> MainSize(AIMAGE_FORMATS format, float aspect = -1.f);

    std::pair<int, int> PreviewSize(std::pair<int, int> mainSize);
};


#endif //PHOTONCAMERA_CAMERA_H
