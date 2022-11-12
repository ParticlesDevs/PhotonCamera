//
// Created by eszdman on 12.11.2022.
//

#ifndef PHOTONCAMERA_PROCESSOR_H
#define PHOTONCAMERA_PROCESSOR_H
#include <thread>
#include <media/NdkImage.h>

class Processor {
private:
    std::mutex lock;
    AImage** buffers;
    void (*callBack)();
public:
    Processor();
    static void Handler(Processor* processor);
    void setProcessedCallback(void (*newCallBack)());
    void Process(AImage **buffer);
};


#endif //PHOTONCAMERA_PROCESSOR_H
