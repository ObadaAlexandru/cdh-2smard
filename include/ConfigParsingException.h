#ifndef CONFIG_PARSING_EXCEPTION_H
#define CONFIG_PARSING_EXCEPTION_H

#include "ErrorCodeException.h"

class ConfigParsingException : public ErrorCodeException {
public:
    ConfigParsingException(std::string msg) : ErrorCodeException("2SMARD-002", msg) {}
};
#endif
