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
  void activate();
  /**
   * Sends a deactivation signal via dbus
   */
  void deactivate();
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
  void callDbusEPS(std::string method);
  sd_bus *bus;
  EPSCaller::HALF half;
  const std::string serviceName = "moveii.eps.service";
  const std::string objectPath = "/moveii/epsdaemon";
  const std::string interfaceName = "moveii.epsdaemon";
  const std::string activationMethodName = "switchOn";
  const std::string deactivationMethodName = "switchOff";
  const std::string signature = "y";
};
#endif
