#include "CliParser.h"
#include "Logger.h"
#include "CliParsingException.h"

#include <iostream>

using namespace std;

const string CliParser::configPathKey = "--config";
const string CliParser::halfOneKey = "--half_1";
const string CliParser::halfTwoKey = "--half_2";

map<string, string> CliParser::getArguments(int argc, const char* argv[]) {
    map<string, string> arguments;
    if(argc > 4) {
      printUsage();
      throw CliParsingException("Too many command line arguments");
    }
    for(int i = 1; i < argc; i++) {
      vector<string> tokens = tokenizer.tokenize(argv[i], "=");
      if(tokens.size() != 2) {
        string argument(argv[i]);
        printUsage();
        throw CliParsingException("Invalid argument " + argument);
      } else {
        arguments[tokens[0]] = tokens[1];
      }
    }
    return arguments;
}

void CliParser::printUsage() {
    Logger::info("Usage: --config=<path> --half_1=<sequence> --half_2=<sequence>\n");
}
