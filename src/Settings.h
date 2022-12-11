#pragma once

#include "SettingsBase.h"
#include "WiFi.h"
#include "Flap.h"
#include "InfluxDBCollector.h"

struct SettingsData {
    NetworkSettings network;
    InfluxDBCollectorSettings influxDB;
    FlapSettings flap1Settings;
    FlapSettings flap2Settings;
};

struct Empty {};

class Settings: public SettingsBase<SettingsData, Empty> {
    public:
        Settings();
        SettingsData* getSettings();

    protected:
        void initializeSettings();
        Empty* getRTCSettings();

    private:
        SettingsData settingsData;
};
