//
// Created by eszdman on 27.10.2022.
//

#include "Camera.h"
#include "main.h"

static void camera_device_on_disconnected(void *context, ACameraDevice *device) {
    LOGI("Camera(id: %s) is diconnected.\n", ACameraDevice_getId(device));
}

static void camera_device_on_error(void *context, ACameraDevice *device, int error) {
    LOGE("Error(code: %d) on Camera(id: %s).\n", error, ACameraDevice_getId(device));
}

static void capture_session_on_ready(void *context, ACameraCaptureSession *session) {
    LOGI("Session is ready. %p\n", session);
}

static void capture_session_on_active(void *context, ACameraCaptureSession *session) {
    LOGI("Session is activated. %p\n", session);
}

static void capture_session_on_closed(void *context, ACameraCaptureSession *session) {
    LOGI("Session is closed. %p\n", session);
}
static void captureCompleted(void* context, ACameraCaptureSession* session,
                             ACaptureRequest* request, const ACameraMetadata* result){
    //LOGI("Capture Completed %p\n", session);
    if(camera.requestedBuffers != 0) {
        if(camera.buffCnt == 0){

        }
        LOGI("Capture Completed buffer count %d\n", camera.buffCnt);
    }
}
static void captureSequenceCompleted(void* context, ACameraCaptureSession* session,
                                     int sequenceId, int64_t frameNumber){
    //LOGI("Capture Completed %p\n", session);

    for(;camera.buffCnt != camera.requestedBuffers;){

    }
    camera.buffCnt = 0;

}
static void onImageAvailable(void* context, AImageReader* reader){
    AImage *image = nullptr;
    AImageReader_acquireNextImage(reader,&image);
    if(camera.buffCnt < MAXFRAMES) {

        //camera.buffers[camera.buffCnt] = image;
        camera.buffCnt++;
        LOGI("Camera read image %d\n",camera.buffCnt);

    }
    AImage_delete(image);
}

void Camera::OpenCamera(ACameraDevice_request_template templateId) {
    ACameraIdList *cameraIdList = nullptr;
    camera.buffers = static_cast<AImage **>(malloc(sizeof(AImage *) * MAXFRAMES));
    LOGI("Created camera.buffers %p\n",camera.buffers);
    const char *selectedCameraId = nullptr;
    camera_status_t camera_status = ACAMERA_OK;
    ACameraManager *cameraManager = ACameraManager_create();

    camera_status = ACameraManager_getCameraIdList(cameraManager, &cameraIdList);
    if (camera_status != ACAMERA_OK) {
        LOGE("Failed to get camera id list (reason: %d)\n", camera_status);
        return;
    }

    if (cameraIdList->numCameras < 1) {
        LOGE("No camera device detected.\n");
        return;
    }

    selectedCameraId = cameraIdList->cameraIds[0];

    LOGI("Trying to open Camera2 (id: %s, num of camera : %d)\n", selectedCameraId,
         cameraIdList->numCameras);

    camera_status = ACameraManager_getCameraCharacteristics(cameraManager, selectedCameraId,
                                                            &cameraCharacteristics);
    ACameraMetadata_getAllTags(cameraCharacteristics, &tagsEntries,&tags);
    if (camera_status != ACAMERA_OK) {
        LOGE("Failed to get camera meta data of ID:%s\n", selectedCameraId);
    }

    deviceStateCallbacks.onDisconnected = camera_device_on_disconnected;
    deviceStateCallbacks.onError = camera_device_on_error;

    camera_status = ACameraManager_openCamera(cameraManager, selectedCameraId,
                                              &deviceStateCallbacks, &cameraDevice);

    if (camera_status != ACAMERA_OK) {
        LOGE("Failed to open camera device (id: %s)\n", selectedCameraId);
    }

    camera_status = ACameraDevice_createCaptureRequest(cameraDevice, templateId,
                                                       &captureRequest);

    if (camera_status != ACAMERA_OK) {
        LOGE("Failed to create preview capture request (id: %s)\n", selectedCameraId);
    }

    ACaptureSessionOutputContainer_create(&captureSessionOutputContainer);

    captureSessionStateCallbacks.onReady = capture_session_on_ready;
    captureSessionStateCallbacks.onActive = capture_session_on_active;
    captureSessionStateCallbacks.onClosed = capture_session_on_closed;

    //ACameraMetadata_free(cameraCharacteristics);
    ACameraManager_deleteCameraIdList(cameraIdList);
    ACameraManager_delete(cameraManager);
}


void Camera::CloseCamera()
{
    camera_status_t camera_status = ACAMERA_OK;
    delete buffers;

    if (captureRequest != nullptr) {
        ACaptureRequest_free(captureRequest);
        captureRequest = nullptr;
    }

    if (cameraOutputTarget != nullptr) {
        ACameraOutputTarget_free(cameraOutputTarget);
        cameraOutputTarget = nullptr;
    }

    if (cameraDevice != nullptr) {
        camera_status = ACameraDevice_close(cameraDevice);

        if (camera_status != ACAMERA_OK) {
            LOGE("Failed to close CameraDevice.\n");
        }
        cameraDevice = nullptr;
    }

    if (sessionOutput != nullptr) {
        ACaptureSessionOutput_free(sessionOutput);
        sessionOutput = nullptr;
    }
    if (inputFrames != nullptr) {
        AImageReader_delete(inputFrames);
        inputFrames = nullptr;
    }

    if (captureSessionOutputContainer != nullptr) {
        ACaptureSessionOutputContainer_free(captureSessionOutputContainer);
        captureSessionOutputContainer = nullptr;
    }

    LOGI("Close Camera\n");
}

void Camera::StartPreview() {
    camera_status_t camera_status = ACAMERA_OK;

    //LOGI("Surface is prepared in %p.\n", surface);

    {
        media_status_t status = AImageReader_getWindow(inputFrames, &readerNativeWindow);
        if (status != AMEDIA_OK) {
            LOGE("Failed to get inputWindow.\n");
        }
        ANativeWindow_acquire(readerNativeWindow);
        camera_status = ACameraOutputTarget_create(readerNativeWindow, &OutputTarget);
        if (camera_status != ACAMERA_OK) {
            LOGE("Failed to create Target Burst.\n");
        }
        camera_status = ACaptureSessionOutput_create(readerNativeWindow, &readerOutput);
        if (camera_status != ACAMERA_OK) {
            LOGE("Failed to create CaptureSession.\n");
        }
        camera_status = ACaptureSessionOutputContainer_add(captureSessionOutputContainer,
                                                           readerOutput);
        if (camera_status != ACAMERA_OK) {
            LOGE("Failed to add readerOutput.\n");
        }
        ACaptureRequest_addTarget(captureRequest, OutputTarget);
    }
    {
        camera_status = ACameraOutputTarget_create(theNativeWindow, &cameraOutputTarget);
        if (camera_status != ACAMERA_OK) {
            LOGE("Failed to create Target preview.\n");
        }
        ACaptureSessionOutput_create(theNativeWindow, &sessionOutput);
        ACaptureSessionOutputContainer_add(captureSessionOutputContainer, sessionOutput);
        ACaptureRequest_addTarget(captureRequest, cameraOutputTarget);
    }

    uint8_t mode = ACAMERA_CONTROL_VIDEO_STABILIZATION_MODE_ON;
    ACaptureRequest_setEntry_u8(captureRequest, ACAMERA_CONTROL_VIDEO_STABILIZATION_MODE, 1,
                                &mode);

    ACameraDevice_createCaptureSession(cameraDevice, captureSessionOutputContainer,
                                       &captureSessionStateCallbacks, &captureSession);
    //ACameraDevice_createCaptureSessionWithSessionParameters(cameraDevice,captureSessionOutputContainer,captureRequest,&captureSessionStateCallbacks,&captureSession);

    captureSessionCaptureCallbacks.onCaptureCompleted = captureCompleted;

    captureSessionCaptureCallbacks.onCaptureSequenceCompleted = captureSequenceCompleted;
    ACameraCaptureSession_setRepeatingRequest(captureSession, &captureSessionCaptureCallbacks, 1,
                                              &captureRequest, nullptr);

}


std::pair<int, int> Camera::MainSize(AIMAGE_FORMATS format, float currentAspect) {
    aspect = currentAspect;
    ACameraMetadata_const_entry entry;
    auto ret = ACameraMetadata_getConstEntry(cameraCharacteristics,ACAMERA_SCALER_AVAILABLE_STREAM_CONFIGURATIONS,&entry);
    if(ret != ACAMERA_OK) {
        LOGE("Error: Missing from characteristics!");
    }

    int height = 0;
    int width = 0;
    LOGD("Size, Type: %d %d",entry.count,entry.type);
    bool found = false;
    for(int i=0; i<int(entry.count);i+=4){
        if(entry.data.i32[i] == format){
            LOGD("Format, Width, Height: %d %d %d",entry.data.i32[i],entry.data.i32[i+1],entry.data.i32[i+2]);
            auto nw = entry.data.i32[i+1];
            auto nh = entry.data.i32[i+2];
            if(currentAspect == 0.f) {
                if (height * width < nw * nh && !(found && (nw * nh > 5000 * 5000))) {
                    height = nh;
                    width = nw;
                    found = true;
                }
            } else {
                if (abs(float(nw)/float(nh) - currentAspect) < 0.05f && height * width < nw * nh && !(found && (nw * nh > 5000 * 5000))) {
                    height = nh;
                    width = nw;
                    found = true;
                }
            }
        }
    }
    if(inputFrames != nullptr){
        AImageReader_delete(inputFrames);
    }
    AImageReader_new(width,height,format,MAXFRAMES,&inputFrames);

    if(format != AIMAGE_FORMAT_YUV_420_888){
        AImageReader_ImageListener listener;
        listener.context = inputFrames;
        listener.onImageAvailable = onImageAvailable;
        AImageReader_setImageListener(inputFrames, &listener);
    }
    rawSize = {width, height};
    return rawSize;
}
std::pair<int, int> Camera::PreviewSize(std::pair<int, int> mainSize) {
    ACameraMetadata_const_entry entry;
    ACameraMetadata_getConstEntry(cameraCharacteristics,ACAMERA_SCALER_AVAILABLE_STREAM_CONFIGURATIONS,&entry);
    float k = float(mainSize.first)/float(mainSize.second);
    int height = 0;
    int width = 0;
    for(int i =0; i<entry.count;i+=4){
        if(entry.data.i32[i] == AIMAGE_FORMAT_YUV_420_888){
            LOGD("Format, Width, Height: %d %d %d",entry.data.i32[i],entry.data.i32[i+1],entry.data.i32[i+2]);
            auto nw = entry.data.i32[i+1];
            auto nh = entry.data.i32[i+2];
            if(nw*nh > height * width && nw * nh < 2000 * 2000 && abs(float(nw) / float(nh) - k) < 0.05f){
                height = nh;
                width = nw;
            }
        }
    }
    previewSize = {width, height};
    return previewSize;
}

