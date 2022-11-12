//
// Created by eszdman on 12.11.2022.
//

#include <Processor.h>
Processor::Processor() {
    std::thread thread(Processor::Handler, this);

}

//Call Processor thread to process dng
void Processor::Process(AImage** buffer) {
    //Loading data
    this->buffers = buffer;
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


        processor->callBack();
    }
}
