#include "main.hpp"

AsyncWebServer server(80);

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

void setup() {
  runBuzzer();
  ServerSetup srv;

  Heidrun_db db;
  db.begin();
  // db.createDatabase("banco_de_teste");
  // Serial.println(db.run_sql("banco_de_teste", "tabela", CREATE_TABLE, "v1 v2 v3").status);
  // for(auto i = 0; i < 10; i++) {
  //   Serial.println(db.run_sql("banco_de_teste", "tabela", INSERT_ROW, "valor1 valor2 valor3").status);
  // }

  // std::vector<String> teste = db.run_sql("banco_de_teste", "tabela", SELECT, "v1 v2 FROM 5").result;

  // for(auto i = 0; i < teste.size(); i++) {
  //   Serial.println(teste[i]);
  // }
  
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SD, "/mdk512/web/index/index.html", "text/html");
  });

  server.on("/teste", HTTP_POST, [](AsyncWebServerRequest *request) {
    request->send(200, "text/plain", "Hello, POST: " + request->arg("teste"));
  });

  server.on("/api/internal", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(200, "application/json", getSystemStatus());
  });

  server.on("/api/external", HTTP_GET, [](AsyncWebServerRequest *request) {
    
  });

  server.serveStatic("/", SD, "/");
  server.begin();
}

void loop() { return; }
