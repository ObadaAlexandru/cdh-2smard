#ifndef CONFIGPARSER_H
#define CONFIGPARSER_H

#include "Tokenizer.h"

#include <string>
#include <utility>
#include <vector>
#include <map>

/**
 * Configuration file parser
 *
 * Able to parse files written in the following form:\n
 *  \# This is a comment\n
 *  parameter_1=value_1\n
 *  parameter_2=value_2\n
 *
 *  Where:\n
 *      keys -> parameter_1, parameter_2\n
 *      values -> value_1, value_2\n
 *
 *
 * N.B. spaces are considered part of the key or value, not trimmed e.g. parameter_1= value_1 is not valid
 */
class ConfigParser {
public:
  /**
   * @param configPath path to the configuration file
   */
  ConfigParser(std::string configPath);
  /**
   * @return the parameters listed in the config file as key-value pair
   */
  std::map<std::string, std::string> getConfigs();
  /**
   * @return a pair of execution sequences as string listed in the config file as half_1, half_2
   */
  std::pair<std::string, std::string> getSequences();
  /**
   * Predefined key for the half_1 sequence
   */
  static const std::string halfOneKey;
  /**
   * Predefined key for the half_2 sequence
   */
  static const std::string halfTwoKey;
  /**
   * Predefined key for the half_1 sensor read pin
   */
  static const std::string pinKeyHalfOne;
  /**
   * Predefined key for the half_2 sensor read pin
   */
  static const std::string pinKeyHalfTwo;
  /**
   * Predefined key for the half_1 sensor activation pin
   */
  static const std::string pinKeyHalfOneActivation;
  /**
   * Predefined key for the half_2 sensor activation pin
   */
  static const std::string pinKeyHalfTwoActivation;
private:
  Tokenizer tokenizer;
  std::map<std::string, std::string> properties;
  const std::string defaultSequenceHalfOne = "A5s|I4000s|A4040s|I300s";
  const std::string defaultSequenceHalfTwo = "A5s|I4000s|A4040s|I300s";
};
#endif
