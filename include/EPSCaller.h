#ifndef EPSCALLER_H
#define EPSCALLER_H

#include <string>

#include <systemd/sd-bus.h>

class EPSCaller {
public:
  enum HALF {
    HALF_ONE,
    HALF_TWO
  };
  EPSCaller(EPSCaller::HALF half);
  void activate();
  void deactivate();
  bool open();
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
