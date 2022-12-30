#include "main.hpp"

ServerSetup::ServerSetup() {
    Serial.begin(9600); // start serial communication
    /*
        By some reason, the ESP32 does not work well with other baud rates other than 9600
        If you change this, the ESP32 will not be able to connect to the WiFi or may not even boot
        I don't know why, but it's a known issue
    */

    // Waits for the SD card to be mounted, if it fails, it will beep the buzzer and try again 
    while (!sd.init()) {
        Serial.println("SD Card Mount Failed");
        runBuzzer(500000);
        delay(1000);
    }

    // Reads the configuration file and stores the words in a vector of tokens
    String config = sd.readFile(SD, "/mdk512/config.conf");
    std::vector<std::string> tokens;
    std::stringstream ss(config.c_str());
    std::string word;
    while(ss >> word) {
        if(word == " ") continue;
        tokens.push_back(word);
    }

    /*
        The configuration file is a text file with the following format:
        NETWORK_SSID <SSID>
        NETWORK_PASSWORD <PASSWORD>
        ALSO OTHER STUFF
    */

    // The code below will read the tokens and store the ssid and password in the ssid and password variables
    for(auto i = 0; i < tokens.size(); i++) {
        if(tokens[i] == "NETWORK_SSID") {
            ssid = tokens[i+1].c_str();
        } else if(tokens[i] == "NETWORK_PASSWORD") {
            password = tokens[i+1].c_str();
        }
    }

    // If the file is not configured, it will exit the program
    if(ssid == "" || password == "") {
        Serial.println("Error: setup file is not configured \n Check the configuration manual");
        Serial.println("E: ssid or password is empty or does not exist");
        exit(1);
    }

    // Connects to the WiFi
    Serial.print("Connecting to "); Serial.println(ssid);
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
