#ifndef CLI_PARSING_EXCEPTION_H
#define CLI_PARSING_EXCEPTION_H

#include "ErrorCodeException.h"

class CliParsingException : public ErrorCodeException {
public:
    CliParsingException(std::string msg) : ErrorCodeException("2SMARD-001", msg) {}
};
#endif
