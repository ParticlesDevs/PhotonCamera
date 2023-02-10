//
// Created by eszdman on 12.11.2022.
//

#include <ProcessorQueue.h>
#define TINY_DNG_WRITER_IMPLEMENTATION
#include "tiny_dng_writer.h"
#include "logs.h"
#include <ProcessingParameters.h>
ProcessorQueue* handle;
static void onProcessed(){

}

ProcessorQueue::ProcessorQueue(){
    handle = this;
}

void ProcessorQueue::post(std::vector<AImage*> buffers) {
    std::string outputFilename = "/sdcard/DCIM/Camera/output.dng";
    std::__fs::filesystem::path path =  "/sdcard/DCIM/Camera/output.dng";
    tinydngwriter::DNGWriter dngWriter(false);
    tinydngwriter::DNGImage dngImage;
    uint8_t* data;
    int dataLength;
    AImage_getPlaneData(buffers[0],0,&data,&dataLength);
    dngImage.SetBigEndian(false);
    int width,height;
    AImage_getWidth(buffers[0],&width);
    AImage_getHeight(buffers[0],&height);
    dngImage.SetImageWidth(width);
    dngImage.SetImageLength(height);
    dngImage.SetRowsPerStrip(height);
    dngImage.SetSamplesPerPixel(1);
    dngImage.SetSoftware("PhotonCamera-" VERSION_NAME VERSION_BUILD " DNG Writer");
    //dngImage.SetUniqueCameraModel()
    unsigned short bps = 16;
    dngImage.SetBitsPerSample(1,&bps);
    dngImage.SetPlanarConfig(tinydngwriter::PLANARCONFIG_CONTIG);
    dngImage.SetCompression(tinydngwriter::COMPRESSION_NONE);
    dngImage.SetPhotometric(tinydngwriter::PHOTOMETRIC_CFA);
    unsigned char cfa[4] = {0,1,1,2};
    dngImage.SetCFAPattern(4,cfa);
    dngImage.SetXResolution(1);
    dngImage.SetYResolution(1);
    //dngImage.SetCustomFieldLong()
    dngImage.SetImageDescription("Test");

    dngImage.SetImageData(data,dataLength);
    dngWriter.AddImage(&dngImage);
    std::string err;
    dngWriter.WriteToFile(path.c_str(),&err);
    if (!err.empty()) {
        std::cerr << err;
    }
    LOGD("Output: %s %s",std::__fs::filesystem::current_path().c_str(),absolute(path).c_str());
    for(auto & buffer : buffers){
        AImage_delete(buffer);
    }
}
