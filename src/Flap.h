#pragma once

#include <Servo.h>
#include "WiFi.h"

const char FLAP_CONFIG_PAGE[] PROGMEM = R"=====(
<fieldset style='display: inline-block; width: 300px'>
<legend>Flap %d</legend>
Open:<br>
<input type="text" name="f%d_open" value="%d"><br>
<small><em>pulse widht in us, i.e. 550</em></small><br><br>
Closed:<br>
<input type="text" name="f%d_close" value="%d"><br>
<small><em>pulse widht in us, i.e. 2300</em></small><br><br>
</fieldset>
)=====";


struct FlapSettings {
    uint16_t closeUs; // us that will result in flap getting closed (default 900)
    uint16_t openUs; // us that will result in flap getting opened (default 770)
};

class Flap {
    public:
        Flap(FlapSettings* settings, uint8_t pin, uint8_t index);
        void begin();
        void loop();
        // In percent. 0 is closed, 100 is fully open.
        void setFlow(uint8_t flow);
        void get_config_page(char* buffer);
        void parse_config_params(WebServerBase* webServer);
        uint8_t getFlow();

        void setDuty(uint16_t);


    private:
        uint16_t flowToServoDutyCycle(uint16_t flow);
        uint8_t _index;
        uint8_t _pin;
        // flow and targetFlow are in 0.1% units. Or 500 means 50% flow.
        uint16_t _duty;
        uint16_t _targetDuty;
        FlapSettings* _settings;
        Servo* _servo;
        uint16_t _countdown = 100;
        uint8_t _flow;
};
