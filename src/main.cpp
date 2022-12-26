#include "main.hpp"

WiFiServer server(80);

void setup() {
  initialBuzzer();
  ServerSetup srv;

  Serial.println(srv.sd.readFile(SD, "/testeSdCard.txt"));

  server.begin();

  // sd.writeFile(SD, "/testeSdCard.txt", "sdjhgjcsdhgfjhdgfjhgjeg \r\n");
  // sd.appendFile(SD, "/testeSdCard.txt", "teste 12349843jfhbdsjhbfjhv\r\n");
}

void loop() {
  delay(2000);
  WiFiClient client = server.available();
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("Connection: close"); // the connection will be closed after completion of the response
  // client.println("Refresh: 5");        // refresh the page automatically every 5 sec
  client.println();
  client.println("<!DOCTYPE html><html><head><title>ESP32 Web Server</title><meta charset='UTF-8'>");
  client.println("<link href='https://cdn.jsdelivr.net/npm/bootstrap@5.2.3/dist/css/bootstrap.min.css' rel='stylesheet' integrity='sha384-rbsA2VBKQhggwzxH7pPCaAqO46MgnOM80zW1RWuH61DGLwZJEdK2Kadq2F9CUG65' crossorigin='anonymous'>");
  client.println("<body> \
    <style> \
        body { \
            background-color: #f5f5f5; \
            max-height: 100vh; \
            max-width: 100vw; \
        }\
    </style>");
  client.println("<div class='container'> \
    <div class='row'> \
        <div class='col-12'> \
            <h1 class='text-center'>ESP32 Web Server</h1> \
        </div> \
    </div> \
    <div class='row'> \
        <div class='col-12'> \
            <h2 class='text-center'> </h2> \
        </div> \
    </div> \
    <div class='row'> \
        <div class='col-12'> \
            <h3 class='text-center'>");

  client.println("</body> \
    </html>");
}