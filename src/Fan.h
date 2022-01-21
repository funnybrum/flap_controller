#pragma once

#include "Arduino.h"

enum FanMode {
    OFF = 0,
    LOW_POWER = 1,
    HIGH_POWER = 2
};

class Fan {
    public:
        Fan(uint8_t onPin=D4, uint8_t lowPowerPin=D3);
        void begin();
        void loop();

        void highPower();
        void lowPower();
        void on();
        void off();
        FanMode getMode();

    private:
        uint8_t _onPin;
        uint8_t _lowPowerPin;
        bool _on;
        bool _highPower;
};
