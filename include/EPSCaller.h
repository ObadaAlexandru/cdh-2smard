#ifndef EPSCALLER_H
#define EPSCALLER_H

#include <string>

#include <systemd/sd-bus.h>
/**
 * EPS dBus interface
 *
 * Provides a dbus interface to the EPS daemon\n
 * One instance is responsible for one half
 */
class EPSCaller {
public:
  enum HALF {
    HALF_ONE,
    HALF_TWO
  };
  /**
   * @param half identifier
   */
  EPSCaller(EPSCaller::HALF half);
  /**
   * Sends an activation signal via dbus
   */
  bool activate();
  /**
   * Sends a deactivation signal via dbus
   */
  bool deactivate();
  /**
   * Opens a dbus connection
   */
  bool open();
  /**
   * Closes dbus connection
   */
  void close();
private:
  int getHalf(EPSCaller::HALF half);
  bool callDbusEPS(std::string method);
  sd_bus *bus;
  EPSCaller::HALF half;
  const std::string serviceName = "moveii.eps";
  const std::string objectPath = "/moveii/eps";
  const std::string interfaceName = "moveii.eps";
  const std::string activationMethodName = "switchOn";
  const std::string deactivationMethodName = "switchOff";
  const std::string inputSignature = "i";
  const std::string outputSignature = "b";
};
#endif
