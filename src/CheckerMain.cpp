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

GPIOPin *pinHalfOneActivation;
GPIOPin *pinHalfTwoActivation;

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

void printStatus(int pinId, string msg) {
    cout << msg << pinId << endl;
}

void deactivateSensors() {
    cout << "====================== SENSOR DEACTIVATION ================\n";
    string deactivationMessage = "Deactivating pin ";
    printStatus(1, deactivationMessage);
    pinHalfOneActivation->setPin(false);
    printStatus(2, deactivationMessage);
    pinHalfTwoActivation->setPin(false);
    usleep(10000000);
    exit(0);
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

    pinHalfOneActivation = new GPIOPin(PinMapper::find(pinKeyHalfOneActivation));
    pinHalfTwoActivation = new GPIOPin(PinMapper::find(pinKeyHalfTwoActivation));

    pinHalfOneActivation->setDirection(GPIOPin::OUTPUT);
    pinHalfTwoActivation->setDirection(GPIOPin::OUTPUT);


    throwIfNotOK(pinHalfOne.isOK(), pinKeyHalfOne);
    throwIfNotOK(pinHalfTwo.isOK(), pinKeyHalfTwo);
    throwIfNotOK(pinHalfOneActivation->isOK(), pinKeyHalfOneActivation);
    throwIfNotOK(pinHalfTwoActivation->isOK(), pinKeyHalfTwoActivation);

    cout << "====================== SENSOR ACTIVATION ==================\n";
    string activationMessage = "Activating pin ";
    printStatus(1, activationMessage);
    pinHalfOneActivation->setPin(true);
    printStatus(2, activationMessage);
    pinHalfTwoActivation->setPin(true);
    usleep(10000000);
    bool halfOneStatus = false;
    bool halfTwoStatus = false;
    while(true) {
        bool newHalfOneStatus = pinHalfOne.readPin();
        bool newHalfTwoStatus = pinHalfTwo.readPin();
        if(newHalfOneStatus != halfOneStatus || newHalfTwoStatus != halfTwoStatus) {
            cout << "====================== 2SMARD STATUS ======================\n";
            printStatus(newHalfOneStatus, 1);
            printStatus(newHalfTwoStatus, 2);
            halfOneStatus = newHalfOneStatus;
            halfTwoStatus = newHalfTwoStatus;
        }
        usleep(1000000);
    }
    cout << "====================== SENSOR DEACTIVATION ================\n";
    deactivateSensors();
    pinHalfOne.close();
    pinHalfTwo.close();
    pinHalfOneActivation->close();
    pinHalfTwoActivation->close();
}

void signalHandler(int signal) {
		cout << "\n================== EXECUTION INTERRUPTED ==================\n";
		cout << "Received signal = " + to_string(signal) + "\n";
    deactivateSensors();
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
