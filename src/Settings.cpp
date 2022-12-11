#include "Settings.h"
#include "Main.h"

Settings::Settings()
    :SettingsBase(&logger) {
}

void Settings::initializeSettings() {
    strcpy(settingsData.network.hostname, HOSTNAME);

    settingsData.flap1Settings.closeUs = 2300;
    settingsData.flap1Settings.openUs = 550;
    settingsData.flap2Settings.closeUs = 2300;
    settingsData.flap2Settings.openUs = 550;
}

SettingsData* Settings::getSettings() {
    return &settingsData;
}

Empty* Settings::getRTCSettings() {
    return NULL;
}
