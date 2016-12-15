#ifndef CONFIGPARSER_H
#define CONFIGPARSER_H

#include "Tokenizer.h"

#include <string>
#include <utility>
#include <vector>
#include <map>

class ConfigParser {
public:
  ConfigParser(std::string);
  std::map<std::string, std::string> getConfigs();
  std::pair<std::string, std::string> getSequences();
  const std::string half_1 = "half_1";
  const std::string half_2 = "half_2";
private:
  Tokenizer tokenizer;
  std::map<std::string, std::string> properties;
};
#endif
