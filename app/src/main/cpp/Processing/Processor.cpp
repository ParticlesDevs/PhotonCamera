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
    auto dngprofile = new DngProfile();
    auto matrix = new CustomMatrix();
    dngprofile->blacklevel = sensor->processing.blackLevel;
    dngprofile->whitelevel = sensor->processing.whiteLevel;
    int width = sensor->processing.rawSize[0];
    int height = sensor->processing.rawSize[1];
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
    matrix->neutralColorVector = sensor->processing.whitePoint;
    matrix->calibrationMatrix1 = sensor->processing.calibrationTransform1;
    matrix->calibrationMatrix2 = sensor->processing.calibrationTransform2;
    matrix->colorMatrix1 = sensor->processing.colorSpaceTransform1;
    matrix->colorMatrix2 = sensor->processing.colorSpaceTransform2;
    matrix->fowardMatrix1 = sensor->processing.forwardMatrix1;
    matrix->fowardMatrix2 = sensor->processing.forwardMatrix2;
    DngWriter* dngWriter = new DngWriter(printf);

    //dngWriter->exifInfo = new ExifInfo();
    //dngWriter->exifInfo->_focallength = 1.0;
    dngWriter->customMatrix = matrix;
    dngWriter->dngProfile = dngprofile;
    dngWriter->rawSize = dataLength;
    dngWriter->bayerBytes = data;
    dngWriter->fileSavePath = "/sdcard/DCIM/Camera/output.dng";
    dngWriter->make = "PhotonCamera";
    dngWriter->model = "v" VERSION_NAME VERSION_BUILD;
    dngWriter->software = "PhotonCamera " "v" VERSION_NAME VERSION_BUILD;
    dngWriter->compression = COMPRESSION_JPEG;

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
    __android_log_vprint(ANDROID_LOG_INFO, "TIFF", format, args);
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
