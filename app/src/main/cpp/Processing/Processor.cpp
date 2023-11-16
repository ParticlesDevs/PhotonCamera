//
// Created by eszdman on 12.11.2022.
//

#include <Processor.h>
#include "DngWriter.h"
#include "logs.h"
Processor::Processor() {
    //std::thread thread(Processor::Handler, this);
}

//Call Processor thread to process dng
void Processor::Process(std::vector<AImage*> buffers) {
    //Loading data
    this->buffers = buffers;
    auto sensor = currentSensor;
    uint8_t* data;
    int dataLength;
    AImage_getPlaneData(buffers[0],0,&data,&dataLength);
    DngProfile* dngprofile = new DngProfile();
    CustomMatrix* matrix = new CustomMatrix();
    dngprofile->blacklevel = sensor->processing.blackLevel;
    dngprofile->whitelevel = sensor->processing.whiteLevel;
    int width = 512;
    int height = 512;
    dngprofile->rawwidht = width;
    dngprofile->rawheight = height;
    dngprofile->rowSize = 0;
    switch (sensor->processing.CFA){
        case 0: {
            dngprofile->bayerformat = "rggb";
            break;
        }
        case 1: {
            dngprofile->bayerformat = "grgb";
            break;
        }
        case 2: {
            dngprofile->bayerformat = "gbrg";
            break;
        }
        case 3: {
            dngprofile->bayerformat = "bggr";
            break;
        }
    }
    dngprofile->rawType = DNG_16BIT;
    /*matrix->neutralColorVector = sensor->processing.whitePoint;
    matrix->calibrationMatrix1 = sensor->processing.calibrationTransform1;
    matrix->calibrationMatrix2 = sensor->processing.calibrationTransform2;
    matrix->colorMatrix1 = sensor->processing.colorSpaceTransform1;
    matrix->colorMatrix2 = sensor->processing.colorSpaceTransform2;
    matrix->fowardMatrix1 = sensor->processing.forwardMatrix1;
    matrix->fowardMatrix2 = sensor->processing.forwardMatrix2;*/
    float ncv[] = {1,1,1};
    matrix->neutralColorVector = ncv;
    float idm[] = {1, 0, 0, 0, 1, 0, 0, 0, 1};
    matrix->colorMatrix1 = idm;
    matrix->colorMatrix2 = idm;
    matrix->fowardMatrix1 = idm;
    matrix->fowardMatrix2 = idm;
    matrix->calibrationMatrix1 = idm;
    matrix->calibrationMatrix2 = idm;
    // = sensor->processing.sensorRect[0];
    DngWriter* dngWriter = new DngWriter(printf);

    auto outBuff = new uint16_t[width*height];
    for(int i =0; i<width; i++){
        for(int j =0; j<height; j++){
            outBuff[i*height+j] = uint16_t(65535.f*(float(i)/float(width - 1) + float(j)/float(height - 1))/2.f);
        }
    }
    //dngWriter->exifInfo = new ExifInfo();
    //dngWriter->exifInfo->_focallength = 1.0;
    dngWriter->customMatrix = matrix;
    dngWriter->dngProfile = dngprofile;
    dngWriter->rawSize = dngprofile->rawwidht*dngprofile->rawheight*2;
    LOGD("Data length: %d", dataLength);
    dngWriter->bayerBytes = reinterpret_cast<unsigned char *>(outBuff);
    dngWriter->fileSavePath = "/sdcard/DCIM/Camera/output.dng";
    dngWriter->_make = "PhotonCamera";
    //dngWriter->_model = (char*) VERSION_NAME VERSION_BUILD;
    dngWriter->_model = "model";
    dngWriter->WriteDNG();

    for(auto & buffer : buffers){
        AImage_delete(buffer);
    }

    lock.lock();
}

void Processor::setProcessedCallback(void (*newCallBack)()) {
    callBack = newCallBack;
}

//Main Processor thread
void Processor::Handler(Processor* processor) {
    while(true){
        processor->lock.unlock();
        //Processing operations


        //processor->callBack();
    }
}

int printf(const char* format, ...){
    va_list args;
    va_start(args, format);
    __android_log_vprint(ANDROID_LOG_INFO, "printf", format, args);
    va_end(args);
    return 0;
}

static void callProcess(Processor* processor, std::vector<AImage*> buffers){
    processor->Process(std::move(buffers));
}

void Processor::post(std::vector<AImage*> buffers) {
    //std::thread thread(callProcess, this, buffers);
    callProcess(this,buffers);
    //std::string outputFilename = "/sdcard/DCIM/Camera/output.dng";
    //std::__fs::filesystem::path path =  "/sdcard/DCIM/Camera/output.dng";
}
