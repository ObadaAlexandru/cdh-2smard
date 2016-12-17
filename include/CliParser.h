#ifndef CLIPARSER_H
#define CLIPARSER_H

#include "Tokenizer.h"

#include <map>
#include <string>

class CliParser {
public:
  std::map<std::string, std::string> getArguments(int argc, const char* argv[]);
  static const std::string configPathKey;
  static const std::string halfOneKey;
  static const std::string halfTwoKey;
private:
  Tokenizer tokenizer;
  void printUsage();
};
#endif
