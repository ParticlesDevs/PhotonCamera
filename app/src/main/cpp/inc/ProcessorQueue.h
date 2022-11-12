//
// Created by eszdman on 12.11.2022.
//

#ifndef PHOTONCAMERA_PROCESSORQUEUE_H
#define PHOTONCAMERA_PROCESSORQUEUE_H

#include <media/NdkImage.h>

class ProcessorQueue {
public:
    int* counter;
    bool locked = false;//Lock for camera new inputs
    void post(AImage **buffers);
};


#endif //PHOTONCAMERA_PROCESSORQUEUE_H
