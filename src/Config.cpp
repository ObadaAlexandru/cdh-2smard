#include "Config.h"
#include <iostream>
#include <cstring>
#include <regex>

std::list<SequenceItem> Config::getSequenceFromString(std::string sequenceString) {
    char cString[sequenceString.size()];
    sequenceString.copy(cString, sizeof cString);
    char *token = std::strtok(cString, "|");
    std::list<SequenceItem> sequence;
    while (token != NULL) {
      sequence.push_back(tokenToSequenceItem(token));
      token = std::strtok(NULL, "|");
    }
    return sequence;
}

SequenceItem Config::tokenToSequenceItem(std::string token) {
    std::regex itemRegex("(A|I)[0-9]*[sm]");
    if (std::regex_match (token, itemRegex)) {
        bool active = token.compare(0, 1, "A");
        int period = std::stoi(token.substr(1, token.size() - 1));
        /**
          If the time unit is minute, convert to seconds
        **/
        period = token.compare(token.size() - 1, token.size(), "m") ? period * 60 : period;
        return SequenceItem(period, active);
    } else {
        /**
          The provided sequence is invalid
        **/
        std::cerr << "Token="<<token<<" is wrong"<<std::endl;
        //TODO Throw exception here
        return NULL;
    }
}
