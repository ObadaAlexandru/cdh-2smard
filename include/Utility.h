#ifndef UTILITY_H
#define UTILITY_H

#include <map>
#include <string>

#define DEFAULT_CONFIG_PATH "./config.cfg"

class Utility {
public:
  /**
   * Parses the command line argumenst as specified in {@link CliParser}
   */
  static std::map<std::string, std::string> getCliArguments(int argc, const char* argv[]);
  /**
   * @return given the map of command line arguments provides the config file path
   */
  static std::string getConfigFilePath(const std::map<std::string, std::string> &cliArguments);
};
#endif
