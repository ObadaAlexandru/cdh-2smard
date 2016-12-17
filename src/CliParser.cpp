#include "CliParser.h"

#include <iostream>

using namespace std;

const string CliParser::configPathKey = "--config";
const string CliParser::halfOneKey = "--half_1";
const string CliParser::halfTwoKey = "--half_2";

map<string, string> CliParser::getArguments(int argc, const char* argv[]) {
  map<string, string> arguments;
  if(argc > 3) {
    cerr << "Too many command line arguments" << '\n';
    printUsage();
    //TODO Throw exception
  }
  for(int i = 1; i < argc; i++) {
    vector<string> tokens = tokenizer.tokenize(argv[i], "=");
    if(tokens.size() != 2) {
      cerr << "Invalid argument "<<argv[i]<<"\n";
      printUsage();
      //TODO Throw exception
    } else {
      arguments[tokens[0]] = tokens[1];
    }
  }
  return arguments;
}

void CliParser::printUsage() {
  cout << "Usage: --config=<path> --half_1=<sequence> --half_2=<sequence>\n";
}
