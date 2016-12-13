#ifndef CONFIG_H
#define CONFIG_H

#include "SequenceItem.h"

#include<string>
#include<list>

class Config {
public:
    std::list<SequenceItem> getSequenceFromString(std::string sequenceString);
private:
    SequenceItem tokenToSequenceItem(std::string token);
};
#endif
