#ifndef _SERVER_SETUP_
#define _SERVER_SETUP_

#include <Arduino.h>

#include <SDCard.hpp>
#include <heidrun.hpp>
#include <sstream> // to be removed, stringstream uses around 20% of the esp flash memory
#include "buzzer.hpp"

#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

// Class to initiate the server, see on config.cpp
class ServerSetup {
    public:
        SDCard sd;
        ServerSetup();
    private:
        const char *ssid;
        const char *password;
};

#endif