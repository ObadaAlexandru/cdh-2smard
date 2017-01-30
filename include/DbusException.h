#ifndef DBUS_EXCEPTION_H
#define DBUS_EXCEPTION_H

#include "ErrorCodeException.h"

class DbusException : public ErrorCodeException {
public:
    DbusException(std::string msg) : ErrorCodeException("2SMARD-003", msg) {}
};
#endif
