//
// Created by eszdman on 27.10.2022.
//

#include "CameraNDK.h"
#include "main.h"
static class CameraNDK* cam;
static void camera_device_on_disconnected(void *context, ACameraDevice *device) {
    LOGI("CameraNDK(id: %s) is diconnected.\n", ACameraDevice_getId(device));
}

static void camera_device_on_error(void *context, ACameraDevice *device, int error) {
    LOGE("Error(code: %d) on CameraNDK(id: %s).\n", error, ACameraDevice_getId(device));
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
    if(cam->parameters->takePicture){
        if(cam->parameters->requestedBuffers == 0){
        LOGI("Capture Started %p\n", session);
        cam->parameters->takePicture = false;
        cam->parameters->requestedBuffers = cam->parameters->maxRequest;
        cam->parameters->buffCnt = 0;
        ACaptureRequest_addTarget(cam->captureRequest, cam->OutputTarget);
        ACameraCaptureSession_setRepeatingRequest(cam->captureSession, &cam->captureSessionCaptureCallbacks, 1,
                                                  &cam->captureRequest, nullptr);
        } else {
            cam->parameters->takePicture = false;
        }
    }

    if(cam->parameters->requestedBuffers != 0) {
        if(cam->parameters->buffCnt >= cam->parameters->requestedBuffers){
            cam->processor->post(buffers);
            LOGI("Capture Burst %d Completed\n", cam->parameters->requestedBuffers);
            cam->parameters->requestedBuffers = 0;
            ACaptureRequest_removeTarget(cam->captureRequest, cam->OutputTarget);
            ACameraCaptureSession_setRepeatingRequest(cam->captureSession, &cam->captureSessionCaptureCallbacks, 1,
                                                      &cam->captureRequest, nullptr);
        }

        LOGI("Capture Completed buffer count %d\n", cam->parameters->buffCnt);
    }
    if(cam->parameters->flipCamera){
        cam->parameters->flipCamera = false;
        cam->parameters->selectedID = (cam->parameters->selectedID+1)%cam->parameters->cameraIDs.size();
        cam->Restart();
    }

}

static void captureSequenceCompleted(void* context, ACameraCaptureSession* session,
                                     int sequenceId, int64_t frameNumber){
    LOGI("Capture Sequence Completed %p\n", session);
}
static void onImageAvailable(void* context, AImageReader* reader){
    AImage *image = nullptr;
    AImageReader_acquireNextImage(reader,&image);

    if(cam->parameters->buffCnt < cam->parameters->requestedBuffers) {
        buffers[cam->parameters->buffCnt] = image;
        cam->parameters->buffCnt++;
        LOGI("CameraNDK read image %d\n",cam->parameters->buffCnt);
        //AImage_delete(image);
    } else {
        AImage_delete(image);
    }
}

void CameraNDK::Reset(){
    if (captureRequest != nullptr) {
        ACaptureRequest_free(captureRequest);
        captureRequest = nullptr;
    }
    auto camera_status = ACameraDevice_createCaptureRequest(cameraDevice,templateID,
                                                       &captureRequest);
    if (camera_status != ACAMERA_OK) {
        LOGE("Failed to create preview capture request (id: %s)\n", parameters->id);
    }

    if (cameraOutputTarget != nullptr) {
        ACameraOutputTarget_free(cameraOutputTarget);
        cameraOutputTarget = nullptr;
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
    ACaptureSessionOutputContainer_create(&captureSessionOutputContainer);
    cam->parameters->rawSize = cam->parameters->currentSensor->rawSizes[cam->parameters->selectedRaw];
    cam->parameters->previewSize = cam->parameters->currentSensor->previewSizes[cam->parameters->selectedPreview];
    cam->parameters->aspect = float(cam->parameters->previewSize.first)/float(cam->parameters->previewSize.second);
    AImageReader_new(cam->parameters->rawSize.first,
                     cam->parameters->rawSize.second,cam->parameters->rawFormat,MAXFRAMES,&inputFrames);
    AImageReader_ImageListener listener;
    listener.context = inputFrames;
    listener.onImageAvailable = onImageAvailable;
    AImageReader_setImageListener(inputFrames, &listener);
    FillCharacteristics();
}

void CameraNDK::Restart(){
    parameters->previewActive = false;
    parameters->id = parameters->cameraIDs[parameters->selectedID].c_str();
    parameters->currentSensor = &parameters->sensors[parameters->selectedID];
    ACameraManager *cameraManager = ACameraManager_create();
    if(cameraCharacteristics != nullptr)
        ACameraMetadata_free(cameraCharacteristics);
    auto camera_status = ACameraManager_getCameraCharacteristics(cameraManager,
                                                                 parameters->id,
                                                            &cameraCharacteristics);

    //ACameraMetadata_getAllTags(cameraCharacteristics, &tagsEntries,&tags);
    if (camera_status != ACAMERA_OK) {
        LOGE("Failed to get camera meta data of ID:%s\n", parameters->id);
    }
    if(captureSession != nullptr)
        ACameraCaptureSession_close(captureSession);
    if(cameraDevice != nullptr)
        ACameraDevice_close(cameraDevice);
    camera_status = ACameraManager_openCamera(cameraManager, parameters->id,
                                              &deviceStateCallbacks, &cameraDevice);

    if (camera_status != ACAMERA_OK) {
        LOGE("Failed to open camera device (id: %s)\n", parameters->id);
    }

    ACameraManager_delete(cameraManager);
    MainSize(static_cast<AIMAGE_FORMATS>(parameters->rawFormat), parameters->aspect);
    LOGD("Selected raw size %d %d",parameters->rawSize.first,parameters->rawSize.second);
    PreviewSize();
    LOGD("Selected preview size %d %d",parameters->previewSize.first,parameters->previewSize.second);
    Reset();
    captureSession = nullptr;
    StartPreview();
}
//Get current sensor entry
ACameraMetadata_const_entry CameraNDK::getEntry(uint32_t tag){
    ACameraMetadata_const_entry entry;
    auto ret = ACameraMetadata_getConstEntry(cameraCharacteristics,tag,&entry);
    if(ret != ACAMERA_OK) {
        LOGE("Error: Missing from characteristics!");
    }
    return entry;
}
void CameraNDK::FillCharacteristics(){
    auto sensor = parameters->currentSensor;
    processor->currentSensor = parameters->currentSensor;
    auto internal = &sensor->processing;

    internal->rawSize[0] = sensor->rawSizes[parameters->currentSensor->selectedRaw].first;
    internal->rawSize[1] = sensor->rawSizes[parameters->currentSensor->selectedRaw].second;
    LOGD("Filling internal parameters");
    auto sensorSize = getEntry(ACAMERA_SENSOR_INFO_PHYSICAL_SIZE);
    auto CFA = getEntry(ACAMERA_SENSOR_INFO_COLOR_FILTER_ARRANGEMENT);
    auto analogISO = getEntry(ACAMERA_SENSOR_MAX_ANALOG_SENSITIVITY);
    auto focal = getEntry(ACAMERA_LENS_INFO_AVAILABLE_FOCAL_LENGTHS);
    auto aperture = getEntry(ACAMERA_LENS_APERTURE);
    auto bl = getEntry(ACAMERA_SENSOR_BLACK_LEVEL_PATTERN);
    auto wl = getEntry(ACAMERA_SENSOR_INFO_WHITE_LEVEL);
    auto ct1 = getEntry(ACAMERA_SENSOR_CALIBRATION_TRANSFORM1);
    auto ct2 = getEntry(ACAMERA_SENSOR_CALIBRATION_TRANSFORM2);
    auto cst1 = getEntry(ACAMERA_SENSOR_COLOR_TRANSFORM1);
    auto cst2 = getEntry(ACAMERA_SENSOR_COLOR_TRANSFORM2);
    auto fm1 = getEntry(ACAMERA_SENSOR_FORWARD_MATRIX1);
    auto fm2 = getEntry(ACAMERA_SENSOR_FORWARD_MATRIX2);

    internal->sensorSize[0] = sensorSize.data.f[0];
    internal->sensorSize[1] = sensorSize.data.f[1];
    internal->CFA = CFA.data.u8[0];
    internal->analogISO = analogISO.data.i32[0];
    internal->focalLength = focal.data.f[0];
    internal->aperture = aperture.data.f[0];
    for(int i =0; i<4;i++)
        internal->blackLevel[i] = float(bl.data.i32[i]);
    internal->whiteLevel = wl.data.i32[0];
    for(int i =0; i<9;i++) {
        internal->calibrationTransform1[i] = float(ct1.data.r[i].numerator)/float(ct1.data.r[i].denominator);
        internal->calibrationTransform2[i] = float(ct2.data.r[i].numerator)/float(ct2.data.r[i].denominator);
        internal->colorSpaceTransform1[i] = float(cst1.data.r[i].numerator)/float(cst1.data.r[i].denominator);
        internal->colorSpaceTransform2[i] = float(cst2.data.r[i].numerator)/float(cst2.data.r[i].denominator);
        internal->forwardMatrix1[i] = float(fm1.data.r[i].numerator)/float(fm1.data.r[i].denominator);
        internal->forwardMatrix2[i] = float(fm2.data.r[i].numerator)/float(fm2.data.r[i].denominator);
    }
    LOGD("Internal parameters done");

}

void CameraNDK::OpenCamera(ACameraDevice_request_template templateId,AIMAGE_FORMATS format, float currentAspect) {
    cam = this;
    templateID = templateId;
    auto tmp = parameters;

    parameters = new CameraParameters();
    processor  = new Processor();
    if(tmp != nullptr){
        parameters->aspect = tmp->aspect;
        delete tmp;
    }
    ACameraIdList *cameraIdList = nullptr;
    LOGI("OpenCamera");
    buffers = std::vector<AImage*>(MAXFRAMES);
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
    parameters->sensors.clear();
    parameters->sensors = std::vector<SensorParameters>(cameraIdList->numCameras);
    for(int i =0; i<cameraIdList->numCameras;i++){
        auto params = SensorParameters();
        parameters->cameraIDs.emplace_back(cameraIdList->cameraIds[i]);
        parameters->sensors[i].id = parameters->cameraIDs[i].c_str();
        LOGD("parameters->sensors[i].id %p",parameters->sensors[i].id);
    }
    parameters->selectedID = 0;
    parameters->id = parameters->cameraIDs[parameters->selectedID].c_str();
    parameters->currentSensor = &parameters->sensors[parameters->selectedID];
    LOGD("parameters->currentSensor %p",parameters->currentSensor->id);
    parameters->rawFormat = format;

    LOGI("Trying to open Camera2 (id: %s, num of camera : %d)\n", parameters->id,
         cameraIdList->numCameras);

    camera_status = ACameraManager_getCameraCharacteristics(cameraManager, parameters->id,
                                                            &cameraCharacteristics);
    //ACameraMetadata_getAllTags(cameraCharacteristics, &tagsEntries,&tags);
    if (camera_status != ACAMERA_OK) {
        LOGE("Failed to get camera meta data of ID:%s\n", parameters->id);
    }

    deviceStateCallbacks.onDisconnected = camera_device_on_disconnected;
    deviceStateCallbacks.onError = camera_device_on_error;

    camera_status = ACameraManager_openCamera(cameraManager, parameters->id,
                                              &deviceStateCallbacks, &cameraDevice);

    if (camera_status != ACAMERA_OK) {
        LOGE("Failed to open camera device (id: %s)\n", parameters->id);
    }

    captureSessionStateCallbacks.onReady = capture_session_on_ready;
    captureSessionStateCallbacks.onActive = capture_session_on_active;
    captureSessionStateCallbacks.onClosed = capture_session_on_closed;

    //ACameraMetadata_free(cameraCharacteristics);
    ACameraManager_deleteCameraIdList(cameraIdList);
    ACameraManager_delete(cameraManager);
    MainSize(format,currentAspect);
    LOGD("Selected raw size %d %d",parameters->rawSize.first,parameters->rawSize.second);
    PreviewSize();
    LOGD("Selected preview size %d %d",parameters->previewSize.first,parameters->previewSize.second);
    Reset();
}


void CameraNDK::CloseCamera()
{
    ACameraCaptureSession_close(cam->captureSession);
    camera_status_t camera_status = ACAMERA_OK;
    buffers.clear();

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

    LOGI("Close CameraNDK\n");
}

void CameraNDK::StartPreview() {
    camera_status_t camera_status = ACAMERA_OK;

    //LOGI("Surface is prepared in %p.\n", surface);

    {
        media_status_t status = AImageReader_getWindow(inputFrames, &readerNativeWindow);
        if (status != AMEDIA_OK) {
            LOGE("Failed to get inputWindow.\n");
        }


        if(OutputTarget != nullptr)
            ACameraOutputTarget_free(OutputTarget);
        camera_status = ACameraOutputTarget_create(readerNativeWindow, &OutputTarget);
        if (camera_status != ACAMERA_OK) {
            LOGE("Failed to create Target Burst.\n");
        }
        if(readerOutput != nullptr)
            ACaptureSessionOutput_free(readerOutput);
        camera_status = ACaptureSessionOutput_create(readerNativeWindow, &readerOutput);
        if (camera_status != ACAMERA_OK) {
            LOGE("Failed to create CaptureSession.\n");
        }
        camera_status = ACaptureSessionOutputContainer_add(captureSessionOutputContainer,
                                                           readerOutput);
        if (camera_status != ACAMERA_OK) {
            LOGE("Failed to add readerOutput.\n");
        }
        //ACaptureRequest_addTarget(captureRequest, OutputTarget);
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
    parameters->previewActive = true;

}

void CameraNDK::MainSize(AIMAGE_FORMATS format, float currentAspect) {
    parameters->currentSensor->rawSizes.clear();
    parameters->aspect = currentAspect;
    ACameraMetadata_const_entry entry = getEntry(ACAMERA_SCALER_AVAILABLE_STREAM_CONFIGURATIONS);

    int height = 0;
    int width = 0;
    LOGD("Size, Type: %d %d",entry.count,entry.type);
    bool found = false;
    auto cnt = 0;
    cam->parameters->rawFormat = format;
    for(int i=0; i<int(entry.count);i+=4){
        if(entry.data.i32[i] == format){
            LOGD("Format, Width, Height: %d %d %d",entry.data.i32[i],entry.data.i32[i+1],entry.data.i32[i+2]);
            auto nw = entry.data.i32[i+1];
            auto nh = entry.data.i32[i+2];
            string build = (std::to_string(nw)+ "X" + std::to_string(nh)+" Raw");
            parameters->currentSensor->rawNames.push_back(build);
            parameters->currentSensor->rawSizes.emplace_back(nw,nh);
            if(currentAspect == 0.f) {
                if (height * width < nw * nh && !(found && (nw * nh > 5000 * 5000))) {
                    height = nh;
                    width = nw;
                    parameters->selectedRaw = cnt;
                    found = true;
                }
            } else {
                if (abs(float(nw)/float(nh) - currentAspect) < 0.05f && height * width < nw * nh && !(found && (nw * nh > 5000 * 5000))) {
                    height = nh;
                    width = nw;
                    parameters->selectedRaw = cnt;
                    found = true;
                }
            }
            cnt++;
        }
    }
     /*if(inputFrames != nullptr){
         AImageReader_delete(inputFrames);
     }
     AImageReader_new(width,height,format,MAXFRAMES,&inputFrames);
     AImageReader_ImageListener listener;
     listener.context = inputFrames;
     listener.onImageAvailable = onImageAvailable;
     AImageReader_setImageListener(inputFrames, &listener);*/
    LOGD("Selected raw size %d %d",width,height);
    parameters->rawSize = parameters->currentSensor->rawSizes[parameters->selectedRaw];
}
void CameraNDK::PreviewSize() {
    parameters->currentSensor->previewSizes.clear();
    ACameraMetadata_const_entry entry = getEntry(ACAMERA_SCALER_AVAILABLE_STREAM_CONFIGURATIONS);
    float k = parameters->aspect;
    int height = 0;
    int width = 0;
    auto cnt = 0;
    for(int i =0; i<entry.count;i+=4){
        if(entry.data.i32[i] == AIMAGE_FORMAT_YUV_420_888){
            LOGD("Format, Width, Height: %d %d %d",entry.data.i32[i],entry.data.i32[i+1],entry.data.i32[i+2]);
            auto nw = entry.data.i32[i+1];
            auto nh = entry.data.i32[i+2];
            string build = (std::to_string(nw)+ "X" + std::to_string(nh)+" Preview");
            parameters->currentSensor->previewNames.push_back(build);
            parameters->currentSensor->previewSizes.emplace_back(nw,nh);
            if(nw*nh > height * width && nw * nh < 2000 * 2000 && abs(float(nw) / float(nh) - k) < 0.05f){
                height = nh;
                width = nw;
                parameters->selectedPreview = cnt;
            }
            cnt++;
        }
    }
    parameters->previewSize = {width,height};
}

