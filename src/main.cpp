#include "main.hpp"

// creates a web server instance
AsyncWebServer server(80);

// function and macro to create a JSON with the system status
#define addJson(var, key, value) var += String("\"" + String(key) + "\":" + String(value) + ",")
String getSystemStatus() {
  String j = "{";
  addJson(j ,"freeHeap", ESP.getFreeHeap());
  addJson(j, "chipRevision", ESP.getChipRevision());
  addJson(j, "macAddress", WiFi.macAddress());
  addJson(j, "rssi", WiFi.RSSI());
  addJson(j, "bssid", WiFi.BSSIDstr());
  addJson(j, "channel", WiFi.channel());
  addJson(j, "subnetMask", WiFi.subnetMask());
  addJson(j, "gatewayIP", WiFi.gatewayIP());
  addJson(j, "dnsIP", WiFi.dnsIP());
  j += "}";
  return j;
}

// creates a database instance
Heidrun_db db;

void setup() {

  // beeps the buzzer to indicate that the device is starting up
  runBuzzer();
  ServerSetup srv; // initiate the server (see on config.cpp)

  db.begin(); // initiate the database
  
  // This route returns a webpage with the system status, such as free heap, mac address, etc.
  // Also contains a list of all the devices in the database and its status
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SD, "/mdk512/web/index/index.html", "text/html");
  });

  // This route returns a JSON with the system status, such as free heap, mac address, etc.
  server.on("/api/internal", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(200, "application/json", getSystemStatus());
  });

  // Serves the static files on the SD card
  server.serveStatic("/", SD, "/");
  server.begin();
}

// loop is not used
void loop() { return; }
