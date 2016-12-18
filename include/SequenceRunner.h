#ifndef SEQUENCERUNNER_H
#define SEQUENCERUNNER_H

#include "SequenceItem.h"
#include "EPSCaller.h"

#include <list>
#include <string>
#include <pthread.h>

#include <moveio/GPIOPin.h>

class SequenceRunner {
public:
  struct RunnerDataEPS {
      std::list<SequenceItem> sequence;
      EPSCaller eps;
      pthread_mutex_t *mutex;
  };
  struct RunnerDataGPIO {
    std::list<SequenceItem> sequence;
    GPIOPin pin;
  };
  SequenceRunner(std::pair<std::list<SequenceItem>, std::list<SequenceItem>> sequences, std::string pinKeyHalfOne, std::string pinKeyHalfTwo);
  void runGPIO();
  void runEPS();
  static void stopRun();
  static bool isStop();
private:
  void tearDown();
  GPIOPin getPin(std::string pinKey);
  static volatile bool stop;
  std::string pinKeyHalfOne;
  std::string pinKeyHalfTwo;
  std::list<SequenceItem> halfOneSequence;
  std::list<SequenceItem> halfTwoSequence;
};
#endif
