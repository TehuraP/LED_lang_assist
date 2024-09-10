
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <Wire.h>
#include "config.h"

#define I2C_SLAVE_ADDR 8

void setup() {
  Serial.begin(9600); 

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD); // Defined in config.h for privacy
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Wire.begin(); // Initialize I2C communication

  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP()); 
}

void loop() {
  HTTPClient http;

  /* Prepares the HTTP client to establish a connection to a web server
     HOST_NAME and PATH_NAME defined in config.h
     HOST_NAME will be your PC's IP address
     PATH_NAME will look something like
      - "/get_words.php" if using Apache server
      - ":18080/get_data" if using Crow server
  */
  String HOST = HOST_NAME;
  String PATH = PATH_NAME;
  http.begin(HOST + PATH); 
  int httpCode = http.GET();

  // httpCode will be negative on error
  if(httpCode > 0) {
    // file found at server
    if(httpCode == HTTP_CODE_OK) {
      String payload = http.getString();
      Serial.println(payload);
      StaticJsonDocument<200> doc;
      DeserializationError error = deserializeJson(doc, payload);
      if (error) {
        Serial.print("JSON Parsing failed: ");
        Serial.println(error.c_str());
      } 
      else {
        // Extract values from JSON
        String english = doc["English"];
        String deutsch = doc["Deutsch"];

        String vocab = english + "," + deutsch;

        // Print the parsed values
        Serial.print("English Level: ");
        Serial.println(english);
        Serial.println(deutsch);
        Wire.beginTransmission(I2C_SLAVE_ADDR); // Start transmission to slave with address 8
        const char* data = vocab.c_str();  // Convert String to const char*
        Wire.write((const uint8_t*)data, strlen(data)); // Send data
        Wire.endTransmission(); // End transmission
        delay(3000);
      }
    } else {
      // HTTP header has been send and Server response header has been handled
      Serial.printf("[HTTP] GET... code: %d\n", httpCode);
    }
  } else {
    Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
    Serial.print("ESP32 IP Address: ");
    Serial.println(WiFi.localIP());
  }

  http.end();

}
