#ifndef _SERVER_SETUP_
#define _SERVER_SETUP_

#include <Arduino.h>
#include <SDCard.hpp>
#include <heidrun.hpp>
#include <sstream>
#include <WiFi.h>
#include "buzzer.hpp"
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

class ServerSetup {
    public:
        SDCard sd;
        ServerSetup();
    private:
        const char *ssid;  // Your ssid
        const char *password;
};

#endif