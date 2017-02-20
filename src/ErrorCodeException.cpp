#include "ErrorCodeException.h"

using namespace std;

ErrorCodeException::ErrorCodeException(string errorCode, string msg) {
    this->errorCode = errorCode;
    this->msg = msg;
}

string ErrorCodeException::getMessage() {
    return errorCode + ": " + msg;
}
