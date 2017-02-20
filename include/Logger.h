#ifndef LOGGER_H
#define LOGGER_H

#include <string>

class Logger {
public:
    static const std::string NOTICE;
    static const std::string INFO;
    static const std::string WARNING;
    static const std::string ERROR;
    static const std::string CRITICAL;

    static void notice(std::string msg);
    static void info(std::string msg);
    static void warn(std::string msg);
    static void error(std::string msg);
    static void critical(std::string msg);
private:
    static void printMessage(std::string msg);
};
#endif
