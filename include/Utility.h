#ifndef UTILITY_H
#define UTILITY_H

#include <map>
#include <string>

#define DEFAULT_CONFIG_PATH "./config.cfg"

class Utility {
public:
  static std::map<std::string, std::string> getCliArguments(int argc, const char* argv[]);
  static std::string getConfigFilePath(const std::map<std::string, std::string> &cliArguments);
};
#endif
