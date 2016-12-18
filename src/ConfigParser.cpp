#include "ConfigParser.h"
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
        cout << "=================== PROPERTIES ============================\n";
        while (getline(configFile, line)) {
            if(!regex_match(line, commentRegex)) {
              vector<string> tokens = tokenizer.tokenize(line, "=");
              if(tokens.size() != 2) {
                  cerr << "Invalid config line: " << line << endl;
                  throw "Invalid config line";
              }
              cout << "Property[" << tokens[0] << "] = " << tokens[1] << endl;
              properties[tokens[0]] = tokens[1];
            } else {
              cout << "Comment: " << line << endl;
            }
        }
    }
    configFile.close();
}

std::pair<std::string, std::string> ConfigParser::getSequences() {
    if(properties.count(halfOneKey) != 1) {
      cout << "Fallback to default sequence 1\n";
      properties[halfOneKey] = defaultSequenceHalfOne;
    }
    if(properties.count(halfTwoKey) != 1) {
      cout << "Fallback to default sequence 2\n";
      properties[halfTwoKey] = defaultSequenceHalfTwo;
    }
    return make_pair (properties[halfOneKey], properties[halfTwoKey]);
}

std::map<string, string> ConfigParser::getConfigs() {
  return properties;
}
