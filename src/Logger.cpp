#include "Logger.h"

#include <iostream>

using namespace std;

const string Logger::NOTICE = "<6>";
const string Logger::INFO = "<5>";
const string Logger::WARNING = "<4>";
const string Logger::ERROR = "<3>";
const string Logger::CRITICAL = "<2>";


void Logger::notice(string msg) {
    cout << Logger::NOTICE << " " << msg;
}

void Logger::info(string msg) {
    cout << Logger::INFO << " " << msg;
}

void Logger::warn(string msg) {
    cout << Logger::WARNING << " " << msg;
}

void Logger::error(string msg) {
    cout << Logger::ERROR << " " << msg;
}

void Logger::critical(string msg) {
    cout << Logger::CRITICAL << " " << msg;
}
