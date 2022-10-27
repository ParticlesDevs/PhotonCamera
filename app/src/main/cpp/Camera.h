//
// Created by eszdman on 27.10.2022.
//

#ifndef PHOTONCAMERA_CAMERA_H
#define PHOTONCAMERA_CAMERA_H
#include <camera/NdkCameraDevice.h>
#include <camera/NdkCameraManager.h>
#include <logs.h>
#include <GLES3/gl3.h>
#include <android/native_window_jni.h>
class Camera {
public:
    GLuint texID;
    ANativeWindow *theNativeWindow;
    ACameraDevice *cameraDevice;
    ACaptureRequest *captureRequest;
    ACameraOutputTarget *cameraOutputTarget;
    ACaptureSessionOutput *sessionOutput;
    ACaptureSessionOutputContainer *captureSessionOutputContainer;
    ACameraCaptureSession *captureSession;

    ACameraDevice_StateCallbacks deviceStateCallbacks;
    ACameraCaptureSession_stateCallbacks captureSessionStateCallbacks;
    void OpenCamera(ACameraDevice_request_template templateId);
    void CloseCamera();
    void StartPreview();
};


#endif //PHOTONCAMERA_CAMERA_H
