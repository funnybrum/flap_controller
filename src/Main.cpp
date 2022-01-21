#include "Main.h"

Logger logger = Logger();
Settings settings = Settings();

WiFiManager wifi = WiFiManager(&logger, &settings.getSettings()->network);
WebServer webServer = WebServer(&logger, &settings.getSettings()->network);
DataCollector dataCollector = DataCollector();
Flap flap1 = Flap(&settings.getSettings()->flap1Settings, D1, 1);
Flap flap2 = Flap(&settings.getSettings()->flap2Settings, D5, 2);
Fan fan = Fan();


void setup()
{ 
    Serial.begin(74880);
    settings.begin();
    flap1.begin();
    flap2.begin();
    fan.begin();
    wifi.begin();
    webServer.begin();

    wifi.connect();
    dataCollector.begin();
}

void loop() {
    wifi.loop();
    webServer.loop();
    settings.loop();
    flap1.loop();
    flap2.loop();
    fan.loop();
    dataCollector.loop();

    if (wifi.isInAPMode() && millis() > 300000L) {
        ESP.reset();
    }

    delay(25);
}
