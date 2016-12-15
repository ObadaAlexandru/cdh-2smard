#include "ConfigParser.h"
#include <fstream>
#include <iostream>
#include <map>
#include <regex>

using namespace std;

ConfigParser::ConfigParser(string configPath) {
    regex commentRegex("(#).*");
    ifstream configFile;
    configFile.open(configPath);
    if(configFile.is_open()) {
        string line;
        while (getline(configFile, line)) {
            if(!regex_match(line, commentRegex)) {
              vector<string> tokens = tokenizer.tokenize(line, "=");
              if(tokens.size() != 2) {
                  cerr << "Invalid config line: " << line << endl;
                  //TODO Throw exception
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
    if(properties.count(half_1) != 1 || properties.count(half_2) != 1) {
        cerr << "Inconsistent configuration" << endl;
        //TODO if sequences don't exist Throw exception
    }
    return std::make_pair (properties[half_1], properties[half_2]);;
}

std::map<string, string> ConfigParser::getConfigs() {
  return properties;
}
