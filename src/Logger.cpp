#include "Logger.h"

#include <iostream>

using namespace std;

const string Logger::NOTICE = "<6>";
const string Logger::INFO = "<5>";
const string Logger::WARNING = "<4>";
const string Logger::ERROR = "<3>";
const string Logger::CRITICAL = "<2>";


void Logger::notice(string msg) {
    printMessage(Logger::NOTICE + " " + msg);
}

void Logger::info(string msg) {
    printMessage(Logger::INFO + " " + msg);
}

void Logger::warn(string msg) {
    printMessage(Logger::WARNING + " " + msg);
}

void Logger::error(string msg) {
    printMessage(Logger::ERROR + " " + msg);
}

void Logger::critical(string msg) {
    printMessage(Logger::CRITICAL + " " + msg);
}

void Logger::printMessage(string msg) {
    cout << msg << endl;
}
