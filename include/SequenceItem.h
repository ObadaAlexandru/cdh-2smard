#ifndef SEQUENCEITEM_H
#define SEQUENCEITEM_H

class SequenceItem {
public:
  SequenceItem(long period);
  SequenceItem(long period, bool active);
  bool isActive();
  long getPeriod();
private:
  long period;
  bool active;
};
#endif
