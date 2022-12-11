#include "Main.h"

char buffer[4096];

WebServer::WebServer(Logger* logger, NetworkSettings* networkSettings)
    :WebServerBase(networkSettings, logger, systemCheck) {
}

void WebServer::registerHandlers() {
    server->on("/", std::bind(&WebServer::handle_root, this));
    server->on("/settings", std::bind(&WebServer::handle_settings, this));
    server->on("/flap1", std::bind(&WebServer::handle_flap1, this));
    server->on("/flap2", std::bind(&WebServer::handle_flap2, this));
}

void WebServer::handle_root() {
    server->sendHeader("Location","/settings");
    server->send(303);
}

void WebServer::handle_settings() {
    wifi.parse_config_params(this);
    dataCollector.parse_config_params(this);
    flap1.parse_config_params(this);
    flap2.parse_config_params(this);

    char network_settings[strlen_P(NETWORK_CONFIG_PAGE) + 32];
    wifi.get_config_page(network_settings);
    
    char data_collector_settings[strlen_P(INFLUXDB_CONFIG_PAGE) + 64];
    dataCollector.get_config_page(data_collector_settings);

    char flap1_settings[strlen_P(FLAP_CONFIG_PAGE) + 32];
    flap1.get_config_page(flap1_settings);

    char flap2_settings[strlen_P(FLAP_CONFIG_PAGE) + 32];
    flap2.get_config_page(flap2_settings);

    sprintf_P(
        buffer,
        CONFIG_PAGE,
        network_settings,
        data_collector_settings,
        flap1_settings,
        flap2_settings);
    server->send(200, "text/html", buffer);
}

void WebServer::handle_flap1() {
    flapCommon(&flap1);
}

void WebServer::handle_flap2() {
    flapCommon(&flap2);
}

void WebServer::flapCommon(Flap* flap) {
    if (server->args() != 1
        || server->arg(0).length() != 0) {
        server->send(400, "text/plain", "try with /flapX?{0-100}");
        return;
    }

    int16_t flow = atoi(server->argName(0).c_str());
    if (flow < 0 || flow > 100) {
        server->send(400, "text/plain", "try with /flapX?{0-100}");
        return;
    }
    
    flap->setFlow(flow);
    server->send(200);
}
