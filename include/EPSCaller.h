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
  uint8_t getHalf(EPSCaller::HALF half);
  void callDbusEPS(std::string method);
  sd_bus *bus;
  EPSCaller::HALF half;
  const std::string serviceName = "moveii.eps.service";
  const std::string objectPath = "/moveii/epsdaemon";
  const std::string interfaceName = "moveii.eps.2smard";
  const std::string activationMethodName = "switchOn";
  const std::string deactivationMethodName = "switchOff";
  const std::string signature = "y";
};
#endif

/* Issue the method call and store the respons message in m */
      //  r = sd_bus_call_method(bus,
      //                         "org.freedesktop.systemd1",           /* service to contact */
      //                         "/org/freedesktop/systemd1",          /* object path */
      //                         "org.freedesktop.systemd1.Manager",   /* interface name */
      //                         "StartUnit",                          /* method name */
      //                         &error,                               /* object to return error in */
      //                         &m,                                   /* return message on success */
      //                         "ss",                                 /* input signature */
      //                         "cups.service",                       /* first argument */
      //                         "replace");                           /* second argument */
