#include "main.hpp"

ServerSetup::ServerSetup() {
    Serial.begin(9600);

    while (!sd.init()) {
        Serial.println("SD Card Mount Failed");
        runBuzzer(500000);
        delay(1000);
    }
    
    String config = sd.readFile(SD, "/config.conf");

    std::vector<std::string> tokens;
    std::stringstream ss(config.c_str());
    std::string word;
    while(ss >> word) {
        if(word == " ") continue;
        tokens.push_back(word);
    }

    for(auto i = 0; i < tokens.size(); i++) {
        if(tokens[i] == "NETWORK_SSID") {
            ssid = tokens[i+1].c_str();
        } else if(tokens[i] == "NETWORK_PASSWORD") {
            password = tokens[i+1].c_str();
        }
    }

    if(ssid == "" || password == "") {
        Serial.println("Error: setup file is not configured \n Check the configuration manual");
        Serial.println("E: ssid or password is empty or does not exist");
        exit(1);
    }

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}
