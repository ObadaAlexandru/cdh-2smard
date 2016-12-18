#include "ConfigParser.h"
#include "CliParser.h"
#include "PinReader.h"
#include "Utility.h"

#include <iostream>
#include <string>

#include <moveio/PinMapper.h>
#include <moveio/GPIOPin.h>

using namespace std;

void printStatus(PinReader &pinReader, int halfId) {
    bool status = pinReader.readStatus();
    string statusAsString = status ? "open" : "closed";
    cout << "HALF[" << halfId << "] = " << statusAsString << endl;
}

void run(int argc, const char* argv[]) {
  if (!PinMapper::valid()) {
      throw "Failed loading pin mapping\n";
  }

  map<string, string> cliArguments = Utility::getCliArguments(argc, argv);
  string configPath = Utility::getConfigFilePath(cliArguments);
  ConfigParser configParser(configPath);
  map<string, string> configs = configParser.getConfigs();
  if(configs.count(CliParser::halfOneKey) != 0) {
      throw "Half one pin not defined, define pin_half_1 property\n";
  }
  if(configs.count(CliParser::halfOneKey) != 0) {
      throw "Half two pin not defined, define pin_half_2 property";
  }
  PinReader pinReaderHalfOne(configs[ConfigParser::pinKeyHalfOne]);
  PinReader pinReaderHalfTwo(configs[ConfigParser::pinKeyHalfTwo]);

  cout << "====================== 2SMARD STATUS ======================\n";
  printStatus(pinReaderHalfOne, 1);
  printStatus(pinReaderHalfTwo, 2);
}

int main(int argc, const char* argv[])
{
    try {
      run(argc, argv);
    } catch(const char* msg) {
			cerr << msg << "\n";
		}
    return 0;
}
