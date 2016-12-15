#ifndef SEQUENCEPARSER_H
#define SEQUENCEPARSER_H

#include "SequenceItem.h"
#include "Tokenizer.h"

#include<string>
#include<list>

class SequenceParser {
public:
  std::list<SequenceItem> getSequenceFromString(std::string sequenceString);
private:
  SequenceItem tokenToSequenceItem(std::string token);
  Tokenizer tokenizer;
};
#endif
