#ifndef SEQUENCEPARSER_H
#define SEQUENCEPARSER_H

#include "SequenceItem.h"
#include "Tokenizer.h"

#include <string>
#include <list>

/**
 * Execution sequence parser
 *
 * Parses 2mard execution sequences.
 * \n Given the following execution sequence A13s|I30m will deserialized into two {@link SequenceItem}
 */
class SequenceParser {
public:
  /**
   * @param sequenceString string representation of an execution sequence e.g. A13s|I30m
   * @return a list of {@link SequenceItem}
   */
  std::list<SequenceItem> getSequenceFromString(std::string sequenceString);
private:
  SequenceItem tokenToSequenceItem(std::string token);
  Tokenizer tokenizer;
};
#endif
