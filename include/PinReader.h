#ifndef PINREADER_H
#define PINREADER_H

#include <string>
#include <iostream>

#include <moveio/GPIOPin.h>

class PinReader {
public:
  PinReader(std::string pinKey);
  bool readStatus();
private:
  std::string pinId;
};
#endif
