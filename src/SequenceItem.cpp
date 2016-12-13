#include "SequenceItem.h"

SequenceItem::SequenceItem(int period) {
    this->period = period;
}

SequenceItem::SequenceItem(int period, bool active) {
    this->period = period;
    this->active = active;
}

int SequenceItem::getPeriod() {
    return period;
}

bool SequenceItem::isActive() {
    return active;
}
