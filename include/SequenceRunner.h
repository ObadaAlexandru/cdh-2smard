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
  struct RunnerData {
      std::list<SequenceItem> sequence;
      EPSCaller::HALF half;
      pthread_mutex_t *mutex;
  };
  SequenceRunner(std::pair<std::list<SequenceItem>, std::list<SequenceItem>> sequences);
  void run();
  static void stopRun();
  static bool isStop();
private:
  void tearDown();
  static volatile bool stop;
  std::list<SequenceItem> halfOneSequence;
  std::list<SequenceItem> halfTwoSequence;
};
#endif
