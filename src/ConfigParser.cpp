#include "ConfigParser.h"
#include "Logger.h"
#include "ConfigParsingException.h"

#include <fstream>
#include <iostream>
#include <map>
#include <regex>

using namespace std;

const string ConfigParser::halfOneKey = "half_1";
const string ConfigParser::halfTwoKey = "half_2";
const string ConfigParser::pinKeyHalfOne = "pin_half_1";
const string ConfigParser::pinKeyHalfTwo = "pin_half_2";
const string ConfigParser::pinKeyHalfOneActivation = "activation_pin_half_1";
const string ConfigParser::pinKeyHalfTwoActivation = "activation_pin_half_2";

ConfigParser::ConfigParser(string configPath) {
    regex commentRegex("(#).*");
    ifstream configFile;
    configFile.open(configPath);
    if(configFile.is_open()) {
        string line;
        Logger::info("=================== PROPERTIES ============================");
        while (getline(configFile, line)) {
            if(!(regex_match(line, commentRegex) || line.find_first_not_of(' ') == string::npos)) {
              vector<string> tokens = tokenizer.tokenize(line, "=");
              if(tokens.size() != 2) {
                  throw ConfigParsingException("Invalid config line: " + line);
              }
              Logger::info("Property[" + tokens[0] + "] = " + tokens[1]);
              properties[tokens[0]] = tokens[1];
            } else {
              Logger::notice("Comment: " + line);
            }
        }
    }
    configFile.close();
}

std::pair<std::string, std::string> ConfigParser::getSequences() {
    if(properties.count(halfOneKey) != 1) {
      Logger::info("Fallback to default sequence 1");
      properties[halfOneKey] = defaultSequenceHalfOne;
    }
    if(properties.count(halfTwoKey) != 1) {
      Logger::info("Fallback to default sequence 2");
      properties[halfTwoKey] = defaultSequenceHalfTwo;
    }
    return make_pair (properties[halfOneKey], properties[halfTwoKey]);
}

std::map<string, string> ConfigParser::getConfigs() {
  return properties;
}
