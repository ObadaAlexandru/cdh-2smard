#include "SequenceParser.h"
#include <iostream>
#include <regex>

using namespace std;

list<SequenceItem> SequenceParser::getSequenceFromString(string sequenceString) {
    vector<string> tokens = tokenizer.tokenize(sequenceString, "|");
    list<SequenceItem> sequence;
    for(string token : tokens) {
      sequence.push_back(tokenToSequenceItem(token));
    }
    return sequence;
}

SequenceItem SequenceParser::tokenToSequenceItem(string token) {
    regex itemRegex("(A|I)[0-9]*[sm]");
    if (regex_match (token, itemRegex)) {
        bool active = token.compare(0, 1, "A");
        int period = stoll(token.substr(1, token.size() - 1));
        /**
          If the time unit is minute, convert to seconds
        **/
        period = token.compare(token.size() - 1, token.size(), "m") ? period * 60 : period;
        return SequenceItem(period, active);
    } else {
        /**
          The provided sequence is invalid
        **/
        cerr << "invalid Token="<<token<<"\n";
        //TODO Throw exception here
        return NULL;
    }
}
