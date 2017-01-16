#ifndef CLIPARSER_H
#define CLIPARSER_H

#include "Tokenizer.h"

#include <map>
#include <string>
/**
 * Command line argument parser
 * Interprets argumets passed in the following format:
 *  argument=<value> e.g. argument_1=my_value
 *
 * Fails if more than three arguments are passed
 */
class CliParser {
public:
  /**
   * @param argc number of arguments
   * @param argv program arguments
   * @return command line arguments as key-value where the argument name is the key
   */
  std::map<std::string, std::string> getArguments(int argc, const char* argv[]);

  /**
   * Predefined key for the config file argument
   */
  static const std::string configPathKey;
  /**
   * Predefined key for the half_1 sequence
   */
  static const std::string halfOneKey;
  /**
   * Predefined key for the half_2 sequence
   */
  static const std::string halfTwoKey;
private:
  Tokenizer tokenizer;
  void printUsage();
};
#endif
