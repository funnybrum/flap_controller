#include "Main.h"

Logger logger = Logger();
Settings settings = Settings();

WiFiManager wifi = WiFiManager(&logger, &settings.getSettings()->network);
WebServer webServer = WebServer(&logger, &settings.getSettings()->network);
Flap flap1 = Flap(&settings.getSettings()->flap1Settings, D1, 1);
Flap flap2 = Flap(&settings.getSettings()->flap2Settings, D5, 2);


void setup()
{ 
    Serial.begin(74880);
    settings.begin();
    flap1.begin();
    flap2.begin();
    wifi.begin();
    webServer.begin();

    wifi.connect();
}

void loop() {
    wifi.loop();
    webServer.loop();
    settings.loop();
    flap1.loop();
    flap2.loop();

    delay(25);
}
