#include "main.hpp"
#include "SD.h"

AsyncWebServer server(80);

void setup() {
  runBuzzer();
  ServerSetup srv;

  Serial.println(srv.sd.readFile(SD, "/testeSdCard.txt"));

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SD, "/index.html", "text/html");
  });

  server.serveStatic("/", SD, "/");
  server.begin();

  // sd.writeFile(SD, "/testeSdCard.txt", "sdjhgjcsdhgfjhdgfjhgjeg \r\n");
  // sd.appendFile(SD, "/testeSdCard.txt", "teste 12349843jfhbdsjhbfjhv\r\n");
}

void loop() {
}