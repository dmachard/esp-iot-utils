#include <WiFiHelper.h>

const char *ssid = "YOUR_SSID";
const char *password = "YOUR_PASSWORD";

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println("\n--- WiFiHelper Example ---");

  // Static helper method to connect to WiFi
  // Works on both ESP32 and ESP8266
  if (WiFiHelper::connect(ssid, password)) {
    Serial.println("Connection successful!");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("Connection failed!");
  }
}

void loop() {
  // Check connection status periodically
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi lost, reconnecting...");
    WiFiHelper::connect(ssid, password);
  }
  delay(10000);
}
