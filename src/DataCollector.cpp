#include "Main.h"
#include "DataCollector.h"

DataCollector::DataCollector():
    InfluxDBCollector(&logger,
                      NULL,
                      &settings.getSettings()->influxDB,
                      &settings.getSettings()->network) {
}

bool DataCollector::shouldCollect() {
    return true;
}

void DataCollector::collectData() {
}

bool DataCollector::shouldPush() {
    return false;
}   

void DataCollector::beforePush() {
    append("rssi", WiFi.RSSI(), 0);
}

void DataCollector::afterPush() {
}