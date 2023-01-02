#include "main.hpp"

// creates a web server instance
AsyncWebServer server(80);

#ifdef __cplusplus
  extern "C" {
 #endif

  uint8_t temprature_sens_read();

#ifdef __cplusplus
}
#endif

#define TOTAL 0
#define USED 1
#define KB 0
#define MB 1
#define GB 2
double_t getSdSize(uint8_t option, uint8_t unit) {
  switch(option) {
    case TOTAL:
      return SD.totalBytes() / (unit == KB ? 1e+3 : unit == MB ? 1e+6 : 1e+9);
    case USED:
      return SD.usedBytes() / (unit == KB ? 1e+3 : unit == MB ? 1e+6 : 1e+9);
  }
}

String stringfy(String str) { return "\"" + str + "\""; }

// function and macro to create a JSON with the system status
#define addJson(var, key, value) var += "\"" + String(key) + "\":" + value + ","
String getSystemStatus() {
  u32_t freeHeap = ESP.getFreeHeap();
  u32_t usedHeap = ESP.getHeapSize() - freeHeap;
  
  String j = "{";
  addJson(j ,"freeHeap", stringfy(String(freeHeap)));
  addJson(j, "usedMemory", stringfy(String(usedHeap)));
  addJson(j, "chipRevision", stringfy(String(ESP.getChipRevision())));
  addJson(j, "coreTemp", stringfy(String((temprature_sens_read() - 32) / 1.8)));

  addJson(j, "sdSize", stringfy(String(getSdSize(TOTAL, MB))));
  addJson(j, "sdUsed", stringfy(String(getSdSize(USED, MB))));

  addJson(j, "macAddress", stringfy(WiFi.macAddress()));
  addJson(j, "rssi", stringfy(String(WiFi.RSSI())));
  addJson(j, "bssid", stringfy(String(WiFi.BSSIDstr())));
  addJson(j, "channel", stringfy(String(WiFi.channel())));
  addJson(j, "subnetMask", stringfy(String(WiFi.subnetMask())));
  addJson(j, "gatewayIP", stringfy(String(WiFi.gatewayIP())));
  addJson(j, "dnsIP", stringfy(String(WiFi.dnsIP())));
  j+= "\"self\": \"heidrun-server\"";
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

  DefaultHeaders::Instance().addHeader("Access-Control-Allow-Origin", "*");
  DefaultHeaders::Instance().addHeader("Access-Control-Allow-Methods", "GET, POST, PUT");
  DefaultHeaders::Instance().addHeader("Access-Control-Allow-Headers", "Content-Type");
  
  // This route returns a webpage with the system status, such as free heap, mac address, etc.
  // Also contains a list of all the devices in the database and its status
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
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
