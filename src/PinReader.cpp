#include "PinReader.h"

#include <moveio/PinMapper.h>

using namespace std;

PinReader::PinReader(string pinKey) {
    pinId = PinMapper::find(pinKey);
    if (pinId.compare("invalid") == 0) {
        throw "Invalid pin key " + pinKey;
    }
    cout << "Using pin " << pinId <<"\n";
}

GPIOPin PinReader::getPin(string pinId) {
    GPIOPin pin(pinId);
    pin.setDirection(GPIOPin::INPUT);
    return pin;
}

bool PinReader::readStatus() {
    GPIOPin pin = getPin(pinId);
    if(pin.isOK()) {
      throw "Not possible to read pin " + pinId;
     }
    bool value = pin.readPin();
    pin.close();
    return value;
}
