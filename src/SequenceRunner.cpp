#include "SequenceRunner.h"
// #include <moveio/GPIOPin.h>

#include <pthread.h>
#include <iostream>
#include <unistd.h>
#include <chrono>

#include <moveio/PinMapper.h>
#include <moveio/GPIOPin.h>


using namespace std;

volatile bool SequenceRunner::stop = false;

SequenceRunner::SequenceRunner(pair<list<SequenceItem> ,list<SequenceItem>> sequences, string pinKeyHalfOne, string pinKeyHalfTwo) {
    this->halfOneSequence = sequences.first;
    this->halfTwoSequence = sequences.second;
    this->pinKeyHalfOne = pinKeyHalfOne;
    this->pinKeyHalfTwo = pinKeyHalfTwo;
}

void* runSequence(void *ptr) {
    SequenceRunner::RunnerData *data = (SequenceRunner::RunnerData*) ptr;
    for(SequenceItem item : data->sequence) {
        auto start_time = std::chrono::high_resolution_clock::now();
        cout << "Set pin to " << item.isActive() << " for " << item.getPeriod() << " seconds\n";
        data->pin.setPin(item.isActive());
        // TODO refactore: use conditional variables and listen on events
        while(item.getPeriod() > chrono::duration_cast<chrono::seconds>(chrono::high_resolution_clock::now() - start_time).count()) {
          usleep(100000);
          if(SequenceRunner::isStop()) {
            cout << "Sequence run has been interrupted\n";
            return NULL;
          }
        }
    }
    return NULL;
}

bool SequenceRunner::isStop() {
  return stop;
}

void SequenceRunner::stopRun() {
  stop = true;
}

void SequenceRunner::tearDown() {
    cout<<"Tear down"<<endl;
}

GPIOPin SequenceRunner::getPin(string pinKey) {
    string pinId = PinMapper::find(pinKey);
    std::cout << "Pin id ===== > " <<pinId<< '\n';
    GPIOPin pin(pinId);
    pin.setDirection(GPIOPin::OUTPUT);
    return pin;
}

void SequenceRunner::run() {
    GPIOPin halfOnePin = getPin(pinKeyHalfOne);
    GPIOPin halfTwoPin = getPin(pinKeyHalfTwo);
    if(!halfOnePin.isOK()) {
        cout << "Half one pin, not ok" <<endl;
        // return;
    }
    if(!halfTwoPin.isOK()) {
        cout << "Half two pin, not ok" <<endl;
        // return;
    }
    RunnerData halfOne = {halfOneSequence, halfOnePin};
    RunnerData halfTwo = {halfTwoSequence, halfTwoPin};
    pthread_t halfOneRunner, halfTwoRunner;
    pthread_create(&halfOneRunner, NULL, &runSequence, &halfOne);
    pthread_create(&halfTwoRunner, NULL, &runSequence, &halfTwo);
    pthread_join(halfOneRunner, NULL);
    pthread_join(halfTwoRunner, NULL);

    halfOnePin.setPin(false);
    halfTwoPin.setPin(false);
    halfOnePin.close();
    halfTwoPin.close();
    tearDown();
}
