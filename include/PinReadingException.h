#ifndef PIN_READING_EXCEPTION_H
#define PIN_READING_EXCEPTION_H

#include "ErrorCodeException.h"

class PinReadingException : public ErrorCodeException {
public:
    PinReadingException(std::string msg) : ErrorCodeException("2SMARD-006", msg) {}
};
#endif
