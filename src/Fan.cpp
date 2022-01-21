#include "Fan.h"
#include "Main.h"

Fan::Fan(uint8_t onPin, uint8_t lowPowerPin) {
    _onPin = onPin;
    _lowPowerPin = lowPowerPin;
}

void Fan::begin() {
    pinMode(_onPin, OUTPUT);
    pinMode(_lowPowerPin, OUTPUT);
    off();
    highPower();
}

void Fan::loop() {

}

void Fan::highPower() {
    logger.log("Fan high");

    digitalWrite(_lowPowerPin, HIGH);
    _highPower = true;
}

void Fan::lowPower() {
    logger.log("Fan low");

    digitalWrite(_lowPowerPin, LOW);
    _highPower = false;
}

void Fan::on() {
    logger.log("Fan on");
    digitalWrite(_onPin, LOW);
    _on = true;
}

void Fan::off(){
    logger.log("Fan off");
    digitalWrite(_onPin, HIGH);
    _on = false;
}

FanMode Fan::getMode() {
    if (_on == false) { 
        return OFF;
    } else if (_highPower == false) {
        return LOW_POWER;
    } else {
        return HIGH_POWER;
    }
}