#ifndef MISSING_PROPERTY_EXCEPTION_H
#define MISSING_PROPERTY_EXCEPTION_H

#include "ErrorCodeException.h"

class MissingPropertyException : public ErrorCodeException {
public:
    MissingPropertyException(std::string msg) : ErrorCodeException("2SMARD-007", msg) {}
};
#endif
