//
// Created by eszdman on 12.11.2022.
//

#ifndef PHOTONCAMERA_PROCESSORQUEUE_H
#define PHOTONCAMERA_PROCESSORQUEUE_H

#include <media/NdkImage.h>
#include <vector>

class ProcessorQueue {
public:
    ProcessorQueue();
    int* counter{};
    bool locked = false;//Lock for camera new inputs

    void post(std::vector<AImage *> buffers);
};


#endif //PHOTONCAMERA_PROCESSORQUEUE_H
