#include "SequenceParser.h"
#include "Logger.h"

#include <iostream>
#include <regex>

using namespace std;

list<SequenceItem> SequenceParser::getSequenceFromString(string sequenceString) {
    if(sequenceString.empty()) {
        throw "Empty sequence string";
    }
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
        bool active = token.at(0) == 'A';
        int period = stoll(token.substr(1, token.size() - 1));
        char timeUnit = token.at(token.size() - 1);
        /**
          If the time unit is minute, convert to seconds
        **/
        period = (timeUnit == 'm') ? period * 60 : period;
        return SequenceItem(period, active);
    } else {
        /**
          The provided sequence is invalid
        **/
        Logger::error("Invalid token=" + token + "\n");
        throw "Invalid token";
    }
}
