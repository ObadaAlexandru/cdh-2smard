#ifndef ERROR_CODE_EXCEPTION_H
#define ERROR_CODE_EXCEPTION_H

#include <string>

class ErrorCodeException {
public:
    ErrorCodeException(std::string errorCode, std::string msg);
    std::string getMessage();
private:
    std::string errorCode;
    std::string msg;
};
#endif
