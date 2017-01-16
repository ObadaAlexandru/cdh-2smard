#!/usr/bin/env python

import dbus

class Client():
   def __init__(self):
      bus = dbus.SessionBus()
      service = bus.get_object('moveii.eps', "/moveii/eps")
      self._message = service.get_dbus_method('switchOn', 'moveii.eps')
      self._quit = service.get_dbus_method('switchOff', 'moveii.eps')

   def run(self):
      print "Mesage from service:", self._message()
      self._quit()

if __name__ == "__main__":
   Client().run()
