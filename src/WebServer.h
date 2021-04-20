#pragma once

#include "Main.h"
#include "WebServerBase.h"
#include "WebPages.h"

class WebServer: public WebServerBase {
    public:
        WebServer(Logger* logger, NetworkSettings* networkSettings);
        void registerHandlers();
        void handle_root();
        void handle_get();
        void handle_settings();
        void handle_reset();
        void handle_blink();
        void handle_flap1();
        void handle_flap2();
        void flapCommon(Flap* flap);
};
