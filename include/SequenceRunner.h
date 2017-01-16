#ifndef SEQUENCERUNNER_H
#define SEQUENCERUNNER_H

#include "SequenceItem.h"
#include "EPSCaller.h"

#include <list>
#include <string>
#include <pthread.h>

/**
 * Given a list of sequence items, sends the activation/deactivation signal to the EPS daemon over dbus
 */
class SequenceRunner {
public:
  /**
   * Execution thread data
   */
  struct RunnerData {
      /**
       * Sequence to be executed
       */
      std::list<SequenceItem> sequence;
      /**
       * Half identifier
       */
      EPSCaller::HALF half;
      /**
       * dbus synchronization mutex
       */
      pthread_mutex_t *mutex;
  };
  /**
   * @param sequences Pair of execution sequences (half_1, half_2) as list of {@link SequenceItem}s
   */
  SequenceRunner(std::pair<std::list<SequenceItem>, std::list<SequenceItem>> sequences);
  /**
   * starts sequence execution
   */
  void run();
  /**
   * Stops sequence execution
   */
  static void stopRun();
  /**
   * Check if is stopped
   * @return true if is stopped false otherwise
   */
  static bool isStop();
private:
  void tearDown();
  static volatile bool stop;
  std::list<SequenceItem> halfOneSequence;
  std::list<SequenceItem> halfTwoSequence;
};
#endif
