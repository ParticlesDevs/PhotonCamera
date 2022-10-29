//
// Created by eszdman on 27.10.2022.
//

#ifndef PHOTONCAMERA_CAMERA_H
#define PHOTONCAMERA_CAMERA_H
#include <camera/NdkCameraDevice.h>
#include <camera/NdkCameraManager.h>
#include <camera/NdkCameraMetadata.h>
#include <camera/NdkCameraMetadataTags.h>
#include <logs.h>
#include <GLES3/gl3.h>
#include <android/native_window_jni.h>
class Camera {
public:
    GLuint texID;
    ANativeWindow *theNativeWindow;
    ACameraMetadata *cameraCharacteristics;
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
};


#endif //PHOTONCAMERA_CAMERA_H
