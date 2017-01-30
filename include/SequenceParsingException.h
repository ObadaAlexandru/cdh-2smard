#ifndef SEQUENCE_PARSING_EXCEPTION_H
#define SEQUENCE_PARSING_EXCEPTION_H

#include "ErrorCodeException.h"

class SequenceParsingException : public ErrorCodeException {
public:
    SequenceParsingException(std::string msg) : ErrorCodeException("2SMARD-004", msg) {}
};
#endif
