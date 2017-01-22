#!/usr/bin/env python

import dbus
import dbus.service
import dbus.mainloop.glib

import gobject

class Service(dbus.service.Object):
   def __init__(self, message):
      self._message = message

   def run(self):
      dbus.mainloop.glib.DBusGMainLoop(set_as_default=True)
      bus_name = dbus.service.BusName("moveii.eps", dbus.SessionBus())
      dbus.service.Object.__init__(self, bus_name, "/moveii/eps")

      self._loop = gobject.MainLoop()
      print "Service running..."
      self._loop.run()
      print "Service stopped"

   @dbus.service.method("moveii.eps", in_signature='q', out_signature='b')
   def switchOn(self, arg):
      print "2SMARD power activated"
      print "Received " + str(int(arg))
      return True

   @dbus.service.method("moveii.eps", in_signature='q', out_signature='b')
   def switchOff(self, arg):
      print "2SMARD power deactivated"
      print "Received " + str(int(arg))
      return True

if __name__ == "__main__":
   Service("This is the service").run()
