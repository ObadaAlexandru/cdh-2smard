#ifndef SEQUENCEITEM_H
#define SEQUENCEITEM_H

/**
 * 2Smard execution item
 *
 * A 2mard execution sequence could have several items e.g. A13s|I10s has two items: A13s and I10s
 * This class is the representation of a single item (Activation state and execution period)
 */
class SequenceItem {
public:
  /**
   * @param period execution period
   */
  SequenceItem(long period);
  /**
   * @param period execution period
   * @param active activation state
   */
  SequenceItem(long period, bool active);
  /**
   * @return the activation state
   */
  bool isActive();
  /**
   * @return the execution period
   */
  long getPeriod();
private:
  long period;
  bool active;
};
#endif
