#include "SequenceRunner.h"
#include "EPSCaller.h"
#include "Logger.h"

#include <string>
#include <iostream>
#include <unistd.h>
#include <chrono>

#include <moveio/PinMapper.h>
#include <moveio/GPIOPin.h>


using namespace std;

volatile bool SequenceRunner::stop = false;

SequenceRunner::SequenceRunner(pair<list<SequenceItem> ,list<SequenceItem>> sequences) {
    this->halfOneSequence = sequences.first;
    this->halfTwoSequence = sequences.second;
}

void* runSequenceEPS(void *ptr) {
    SequenceRunner::RunnerData *data = (SequenceRunner::RunnerData*) ptr;
    EPSCaller epsCaller(data->half);
    epsCaller.open();
    for(SequenceItem item : data->sequence) {
        auto start_time = std::chrono::high_resolution_clock::now();
        while (true && !SequenceRunner::isStop()) {
            pthread_mutex_lock(data->mutex);
            try {
            if(item.isActive()) {
                Logger::info("Send active to half_" + to_string(data->half));
                if(epsCaller.activate()) {
                    break;
                } else {
                    Logger::error("EPS daemon didn't execute the activation command for half_" + to_string(data->half));
                    usleep(100000);
                    Logger::info("Retrying");
                }
            } else {
                Logger::info("Send inactive to half_" + to_string(data->half));
                if(epsCaller.deactivate()) {
                    break;
                } else {
                    Logger::error("EPS daemon didn't execute the deactivation command for half_" + to_string(data->half));
                    usleep(100000);
                    Logger::info("Retrying");
                }
            }
          } catch (const char* msg) {
              Logger::error("Error while accessing EPS daemon. Sequence execution will stop");
              SequenceRunner::stopRun();
          }
        }
        pthread_mutex_unlock(data->mutex);
        while(item.getPeriod() > chrono::duration_cast<chrono::seconds>(chrono::high_resolution_clock::now() - start_time).count()) {
          usleep(100000);
          if(SequenceRunner::isStop()) {
            epsCaller.close();
            return NULL;
          }
        }
    }
    epsCaller.close();
    return NULL;
}

bool SequenceRunner::isStop() {
  return stop;
}

void SequenceRunner::stopRun() {
  stop = true;
}

void SequenceRunner::tearDown() {
    Logger::info("================== 2SMARD Deactivation routine ============");
    EPSCaller callerHalfOne(EPSCaller::HALF_ONE);
    EPSCaller callerHalfTwo(EPSCaller::HALF_TWO);
    auto printFunc = [](int halfId) {Logger::info("Deactivating 2SMARD half " + to_string(halfId));};
    callerHalfOne.open();
    callerHalfTwo.open();
    printFunc(1);
    callerHalfOne.deactivate();
    printFunc(2);
    callerHalfTwo.deactivate();
    callerHalfOne.close();
    callerHalfTwo.close();
}

void SequenceRunner::run() {
    Logger::info("================== Sequence execution =====================");
    pthread_mutex_t mutex;
    pthread_mutex_init(&mutex, NULL);
    RunnerData halfOne = {halfOneSequence, EPSCaller::HALF_ONE, &mutex};
    RunnerData halfTwo = {halfTwoSequence, EPSCaller::HALF_TWO, &mutex};
    pthread_t halfOneRunner, halfTwoRunner;
    pthread_create(&halfOneRunner, NULL, &runSequenceEPS, &halfOne);
    pthread_create(&halfTwoRunner, NULL, &runSequenceEPS, &halfTwo);
    pthread_join(halfOneRunner, NULL);
    pthread_join(halfTwoRunner, NULL);
    tearDown();
}
