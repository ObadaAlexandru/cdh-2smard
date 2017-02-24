#include "EPSCaller.h"
#include "Logger.h"
#include "DbusException.h"

#include <iostream>

#include <errno.h>
#include <systemd/sd-bus.h>
#include <fstream>
#include <string>
#include <systemd/sd-bus.h>

using namespace std;

EPSCaller::EPSCaller(EPSCaller::HALF half) {
    this->half = half;
    int response = sd_bus_open_system(&bus);
    if (response < 0) {
          string msg = Logger::ERROR + " Failed to connect to system bus: %s\n";
          fprintf(stderr, msg.c_str(), strerror(-response));
          throw DbusException("Failed opening dbus connection");
    }
}

string EPSCaller::getHalf(EPSCaller::HALF half) {
    switch (half) {
      case HALF_ONE:
        return "2SMARD1";
      case HALF_TWO:
        return "2SMARD2";
      default:
        throw "Unknown half identifier";
    }
}

bool EPSCaller::callDbusEPS(string method) {
      sd_bus_error error = SD_BUS_ERROR_NULL;
      sd_bus_message *message = NULL;
      bool status;
      int response = sd_bus_call_method(bus,
                             serviceName.c_str(),
                             objectPath.c_str(),
                             interfaceName.c_str(),
                             method.c_str(),
                             &error,
                             &message,
                             inputSignature.c_str(),
                             getHalf(half).c_str());
      if (response < 0) {
          string msg = Logger::ERROR + " 2SMARD %s failed: %s\n";
          fprintf(stderr, msg.c_str(), method.c_str(), error.message);
          throw DbusException("Failed calling eps");
      }

      response = sd_bus_message_read(message, outputSignature.c_str(), &status);

      if (response < 0) {
          string msg = Logger::ERROR + " 2SMARD %s failed: %s\n";
          fprintf(stderr, msg.c_str(), method.c_str(), error.message);
          throw DbusException("Failed reading eps result");
      }
      sd_bus_error_free(&error);
      sd_bus_message_unref(message);
      return status;
  }

bool EPSCaller::activate() {
    return callDbusEPS(activationMethodName);
}

bool EPSCaller::deactivate() {
    return callDbusEPS(deactivationMethodName);
}

EPSCaller::~EPSCaller() {
    sd_bus_flush_close_unref(bus);
}
