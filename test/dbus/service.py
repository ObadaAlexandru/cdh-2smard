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
      bus_name = dbus.service.BusName("moveii.eps.service", dbus.SessionBus())
      dbus.service.Object.__init__(self, bus_name, "/moveii/epsdaemon")

      self._loop = gobject.MainLoop()
      print "Service running..."
      self._loop.run()
      print "Service stopped"

   @dbus.service.method("moveii.epsdaemon", in_signature='y', out_signature='')
   def switchOn(self, arg):
      print "2SMARD power activated"
      print "Received " + str(int(arg))

   @dbus.service.method("moveii.epsdaemon", in_signature='y', out_signature='')
   def switchOff(self, arg):
      print "2SMARD power deactivated"
      print "Received " + str(int(arg))

if __name__ == "__main__":
   Service("This is the service").run()
