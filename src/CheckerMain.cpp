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
#include <csignal>

using namespace std;

static volatile bool running = true;

void printStatus(bool pinStatus, int halfId) {
    string statusAsString = pinStatus ? "open" : "closed";
    cout << "HALF[" << halfId << "] = " << statusAsString << endl;
}

void printSensorsStatus(bool halfOne, bool halfTwo) {
    cout << "====================== 2SMARD STATUS ======================\n";
    printStatus(halfOne, 1);
    printStatus(halfTwo, 2);
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

void printStatus(int pinId, string msg) {
    cout << msg << pinId << endl;
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

    GPIOPin pinHalfOne(PinMapper::find(pinKeyHalfOne));
    GPIOPin pinHalfTwo(PinMapper::find(pinKeyHalfTwo));
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
    string activationMessage = "Activating pin ";
    printStatus(1, activationMessage);
    pinHalfOneActivation.setPin(true);
    printStatus(2, activationMessage);
    pinHalfTwoActivation.setPin(true);
    usleep(10000000);
    bool halfOneStatus = pinHalfOne.readPin();
    bool halfTwoStatus = pinHalfTwo.readPin();
    printSensorsStatus(halfOneStatus, halfTwoStatus);
    while(running) {
        bool newHalfOneStatus = pinHalfOne.readPin();
        bool newHalfTwoStatus = pinHalfTwo.readPin();
        if(newHalfOneStatus != halfOneStatus || newHalfTwoStatus != halfTwoStatus) {
            printSensorsStatus(newHalfOneStatus, newHalfTwoStatus);
            halfOneStatus = newHalfOneStatus;
            halfTwoStatus = newHalfTwoStatus;
        }
        usleep(1000000);
    }
    cout << "====================== SENSOR DEACTIVATION ================\n";
    string deactivationMessage = "Deactivating pin ";
    printStatus(1, deactivationMessage);
    pinHalfOneActivation.setPin(false);
    printStatus(2, deactivationMessage);
    pinHalfTwoActivation.setPin(false);
    usleep(2000000);
    pinHalfOne.close();
    pinHalfTwo.close();
    pinHalfOneActivation.close();
    pinHalfTwoActivation.close();
}

void signalHandler(int signal) {
		cout << "\n================== EXECUTION INTERRUPTED ==================\n";
		cout << "Received signal = " + to_string(signal) + "\n";
    running = false;
}

int main(int argc, const char* argv[])
{
    try {
      signal(SIGINT, signalHandler);
      signal(SIGTERM, signalHandler);
      run(argc, argv);
    } catch(ErrorCodeException& exception) {
			cerr << exception.getMessage() << "\n";
      return 1;
		} catch (...) {
      cerr << "2SMARD-005: Unexpected exception\n";
      return 2;
    }
    return 0;
}
