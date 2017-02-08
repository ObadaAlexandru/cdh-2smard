#include "ConfigParser.h"
#include "CliParser.h"
#include "Utility.h"
#include "PinReadingException.h"
#include "MissingPropertyException.h"

#include <iostream>
#include <string>
#include <unistd.h>

#include <moveio/PinMapper.h>
#include <moveio/GPIOPin.h>

using namespace std;

void printStatus(bool pinStatus, int halfId) {
    string statusAsString = pinStatus ? "open" : "closed";
    cout << "HALF[" << halfId << "] = " << statusAsString << endl;
}

string getPinId(string pinKey) {
    string pinId = PinMapper::find(pinKey);
    if (pinId.compare("invalid") == 0) {
        throw PinReadingException("Pin<" + pinKey + "> is not valid");
    }
    cout << "Using pin " << pinId <<"\n";
    return pinId;
}

void throwIfNotOK(bool isOK, string pinId) {
    if(!isOK) {
        throw PinReadingException("Not possible to read pin<" + pinId + ">");
    }
}

void checkIfDefined(map<string, string> &properties, string key) {
  if(properties.count(key) == 0) {
      throw MissingPropertyException("Property " + key + " undefined");
  }
}

void run(int argc, const char* argv[]) {
  if (!PinMapper::valid()) {
      throw PinReadingException("Failed loading pin map");
  }

  map<string, string> cliArguments = Utility::getCliArguments(argc, argv);
  string configPath = Utility::getConfigFilePath(cliArguments);
  ConfigParser configParser(configPath);
  map<string, string> configs = configParser.getConfigs();
  checkIfDefined(configs, ConfigParser::pinKeyHalfTwo);
  checkIfDefined(configs, ConfigParser::pinKeyHalfTwo);
  checkIfDefined(configs, ConfigParser::pinKeyHalfOneActivation);
  checkIfDefined(configs, ConfigParser::pinKeyHalfTwoActivation);

  string pinKeyHalfOne = configs[ConfigParser::pinKeyHalfOne];
  string pinKeyHalfTwo = configs[ConfigParser::pinKeyHalfTwo];
  string pinKeyHalfOneActivation = configs[ConfigParser::pinKeyHalfOneActivation];
  string pinKeyHalfTwoActivation = configs[ConfigParser::pinKeyHalfTwoActivation];

  GPIOPin pinHalfOne(PinMapper::find(pinKeyHalfOneActivation));
  GPIOPin pinHalfTwo(PinMapper::find(pinKeyHalfOneActivation));
  pinHalfOne.setDirection(GPIOPin::INPUT);
  pinHalfTwo.setDirection(GPIOPin::INPUT);

  GPIOPin pinHalfOneActivation(PinMapper::find(pinKeyHalfOneActivation));
  GPIOPin pinHalfTwoActivation(PinMapper::find(pinKeyHalfTwoActivation));

  pinHalfOneActivation.setDirection(GPIOPin::OUTPUT);
  pinHalfTwoActivation.setDirection(GPIOPin::OUTPUT);


  throwIfNotOK(pinHalfOne.isOK(), pinKeyHalfOne);
  throwIfNotOK(pinHalfTwo.isOK(), pinKeyHalfTwo);
  throwIfNotOK(pinHalfOneActivation.isOK(), pinKeyHalfOneActivation);
  throwIfNotOK(pinHalfTwoActivation.isOK(), pinKeyHalfTwoActivation);

  cout << "====================== SENSOR ACTIVATION ==================\n";
  auto printFunction = [](int pinId, string msg) { cout << msg << pinId << endl;};
  string activationMessage = "Activating pin ";
  printFunction(1, activationMessage);
  pinHalfOneActivation.setPin(true);
  printFunction(2, activationMessage);
  pinHalfTwoActivation.setPin(true);
  usleep(5000000);
  cout << "====================== 2SMARD STATUS ======================\n";
  printStatus(pinHalfOne.readPin(), 1);
  printStatus(pinHalfTwo.readPin(), 2);
  cout << "====================== SENSOR DEACTIVATION ================\n";
  string deactivationMessage = "Deactivating pin ";
  printFunction(1, deactivationMessage);
  pinHalfOneActivation.setPin(false);
  printFunction(2, deactivationMessage);
  pinHalfTwoActivation.setPin(false);
  usleep(5000000);

  pinHalfOne.close();
  pinHalfTwo.close();
  pinHalfOneActivation.close();
  pinHalfTwoActivation.close();

}

int main(int argc, const char* argv[])
{
    try {
      run(argc, argv);
    } catch(ErrorCodeException& exception) {
			cerr << exception.getMessage() << "\n";
      return 1;
		}
    return 0;
}
