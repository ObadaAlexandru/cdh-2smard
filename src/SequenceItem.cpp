#include "SequenceItem.h"

SequenceItem::SequenceItem(long period) {
    this->period = period;
}

SequenceItem::SequenceItem(long period, bool active) {
    this->period = period;
    this->active = active;
}

long SequenceItem::getPeriod() {
    return period;
}

bool SequenceItem::isActive() {
    return active;
}
