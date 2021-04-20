#include <Flap.h>
#include <Main.h>

Flap::Flap(FlapSettings* settings, uint8_t pin, uint8_t index) {
    _settings = settings;
    _pin = pin;
    _index = index;
}

void Flap::begin() {
    _servo = new Servo();
    _servo->attach(_pin, 450, 2600, _settings->openUs);
    _duty = _targetDuty = _settings->openUs;
}

void Flap::loop() {
    bool change = false;
    if (_duty > _targetDuty) {
        _duty--;
        change = true;
    } else if (_duty < _targetDuty) {
        _duty++;
        change = true;
    }

    if (change) {
        _servo->attach(_pin, 450, 2600, _duty);
    } else {
        if (_countdown > 0) {
            _countdown--;
        } else {
            _servo->detach();
        }
    }
}

// 0 - valve is closed, servo is at closeUs
// 100 - valve is open, servo is at openUs
uint16_t Flap::flowToServoDutyCycle(uint16_t flow) {
    // Calculate the flap degrees. 100 flow is valve open (low US), 0 flow is valve closed (high us)
    // So we want for 1000 input flow to get 0 and for 0 input flow to get PI/2.
    double rad = acos((1000-flow) / 1000.0);

    // Now map it to duty cyclse in microseconds.
    // 0 means flap is closed or the result should be closeUs (low value).
    // PI/2 means the flap is open or the result should be openUs (high value).
    // Multiply by 1000- for better resolution. The map function works only with integers.
    return map(
        rad * 10000,
        0,
        PI * 10000 / 2,
        _settings->closeUs,
        _settings->openUs);
}

void Flap::setFlow(uint8_t flow) {
    _targetDuty = flowToServoDutyCycle(flow * 10);
}

void Flap::get_config_page(char* buffer) {
    sprintf_P(
        buffer,
        FLAP_CONFIG_PAGE,
        _index,
        _index,
        _settings->openUs,
        _index,
        _settings->closeUs);
}

void Flap::parse_config_params(WebServerBase* webServer) {
    if (_index == 1) {
        webServer->process_setting("f1_open", _settings->openUs);    
        webServer->process_setting("f1_close", _settings->closeUs);    
    } else if (_index == 2) {
        webServer->process_setting("f2_open", _settings->openUs);    
        webServer->process_setting("f2_close", _settings->closeUs);    
    }
}
