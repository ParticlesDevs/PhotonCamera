//
// Created by eszdman on 12.11.2022.
//

#ifndef PHOTONCAMERA_PROCESSOR_H
#define PHOTONCAMERA_PROCESSOR_H
#include <thread>
#include <media/NdkImage.h>
#include <vector>
#include <ProcessingParameters.h>
#include "CameraParameters.h"

class Processor {
private:
    std::mutex lock;
    std::vector<AImage*> buffers;
    void (*callBack)();
public:
    SensorParameters *currentSensor;
    int* counter{};
    bool locked = false;//Lock for camera new inputs
    Processor();
    static void Handler(Processor* processor);
    void setProcessedCallback(void (*newCallBack)());
    void Process(std::vector<AImage*> buffers);
    void post(std::vector<AImage *> buffers);
};


#endif //PHOTONCAMERA_PROCESSOR_H
