#ifndef SEQUENCEITEM_H
#define SEQUENCEITEM_H

class SequenceItem {
public:
  SequenceItem(int period);
  SequenceItem(int period, bool active);
  bool isActive();
  int getPeriod();
private:
  int period;
  bool active;
};

#endif
