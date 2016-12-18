#ifndef CONFIGPARSER_H
#define CONFIGPARSER_H

#include "Tokenizer.h"

#include <string>
#include <utility>
#include <vector>
#include <map>

class ConfigParser {
public:
  ConfigParser(std::string configPath);
  std::map<std::string, std::string> getConfigs();
  std::pair<std::string, std::string> getSequences();
  static const std::string halfOneKey;
  static const std::string halfTwoKey;
  static const std::string pinKeyHalfOne;
  static const std::string pinKeyHalfTwo;
  static const std::string pinKeyHalfOneActivation;
  static const std::string pinKeyHalfTwoActivation;
private:
  Tokenizer tokenizer;
  std::map<std::string, std::string> properties;
  const std::string defaultSequenceHalfOne = "A300m|I4000s|A4040s|I300s";
  const std::string defaultSequenceHalfTwo = "A300m|I4000s|A4040s|I300s";
};
#endif
