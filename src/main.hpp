#ifndef _SERVER_SETUP_
#define _SERVER_SETUP_

#include <Arduino.h>
#include <SDCard.hpp>
#include <vector>
#include <string>
#include <sstream>
#include <WiFi.h>

class ServerSetup {
    public:
        SDCard sd;
        ServerSetup();
    private:
        const char *ssid;  // Your ssid
        const char *password;
};

#endif