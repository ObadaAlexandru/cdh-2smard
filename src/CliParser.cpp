#include "CliParser.h"
#include "Logger.h"

#include <iostream>

using namespace std;

const string CliParser::configPathKey = "--config";
const string CliParser::halfOneKey = "--half_1";
const string CliParser::halfTwoKey = "--half_2";

map<string, string> CliParser::getArguments(int argc, const char* argv[]) {
    map<string, string> arguments;
    if(argc > 4) {
      Logger::error("Too many command line arguments\n");
      printUsage();
      throw "Invlaid argument list";
    }
    for(int i = 1; i < argc; i++) {
      vector<string> tokens = tokenizer.tokenize(argv[i], "=");
      if(tokens.size() != 2) {
        string argument(argv[i]);
        Logger::error("Invalid argument " + argument + "\n");
        printUsage();
        throw "Invalid argument";
      } else {
        arguments[tokens[0]] = tokens[1];
      }
    }
    return arguments;
}

void CliParser::printUsage() {
    Logger::info("Usage: --config=<path> --half_1=<sequence> --half_2=<sequence>\n");
}
