#include "Utility.h"
#include "CliParser.h"
#include "Logger.h"

#include <iostream>

using namespace std;

std::map<std::string, std::string> Utility::getCliArguments(int argc, const char* argv[]) {
  CliParser cliParser;
  map<string, string> cliArguments;
  if(argc > 1) {
    Logger::info("Command line arguments provided\n");
    cliArguments = cliParser.getArguments(argc, argv);
  }
  return cliArguments;
}
std::string Utility::getConfigFilePath(const std::map<std::string, std::string> &cliArguments) {
  if(cliArguments.count(CliParser::configPathKey) != 0) {
      return cliArguments.find(CliParser::configPathKey)->second;
  }
  return DEFAULT_CONFIG_PATH;
}
