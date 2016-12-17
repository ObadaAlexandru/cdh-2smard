#ifndef SEQUENCERUNNER_H
#define SEQUENCERUNNER_H

#include "SequenceItem.h"


#include <moveio/GPIOPin.h>
#include <list>
#include <string>

class SequenceRunner {
public:
  struct RunnerData {
      std::list<SequenceItem> sequence;
      GPIOPin pin;
  };
  SequenceRunner(std::pair<std::list<SequenceItem>, std::list<SequenceItem>> sequences, std::string pinKeyHalfOne, std::string pinKeyHalfTwo);
  void run();
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
