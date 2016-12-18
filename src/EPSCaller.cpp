#include "EPSCaller.h"

#include <iostream>

#include <errno.h>
#include <systemd/sd-bus.h>
#include <fstream>
#include <string>

#include <systemd/sd-bus.h>

using namespace std;

EPSCaller::EPSCaller(EPSCaller::HALF half) {
    this->half = half;
}

bool EPSCaller::open() {
    int response = sd_bus_open_system(&bus);
    if (response < 0) {
          fprintf(stderr, "Failed to connect to system bus: %s\n", strerror(-response));
          //TODO throw exception
    }
    return true;
}

uint8_t EPSCaller::getHalf(EPSCaller::HALF half) {
    switch (half) {
      case HALF_ONE:
        return 1;
      case HALF_TWO:
        return 2;
      default:
        throw "Unknown half identifier";
    }
}

void EPSCaller::callDbusEPS(string method) {
    sd_bus_error error = SD_BUS_ERROR_NULL;
    sd_bus_message *message = NULL;
    int response = sd_bus_call_method(bus,
                           serviceName.c_str(),
                           objectPath.c_str(),
                           interfaceName.c_str(),
                           method.c_str(),
                           &error,
                           &message,
                           signature.c_str(),
                           getHalf(half));
    if (response < 0) {
        fprintf(stderr, "2SMARD %s failed: %s\n", method.c_str(), error.message);
    }
    sd_bus_error_free(&error);
    sd_bus_message_unref(message);
}

void EPSCaller::activate() {
    callDbusEPS(activationMethodName);
}

void EPSCaller::deactivate() {
    callDbusEPS(activationMethodName);
}

void EPSCaller::close() {
    sd_bus_unref(bus);
}
