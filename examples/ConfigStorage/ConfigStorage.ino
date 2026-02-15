#include <ConfigHelper.h>

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println("\n--- ConfigHelper Example ---");

  // ConfigHelper uses Preferences on ESP32 to store data persistently.
  // It uses a "namespace" to group settings.
  const char *ns = "my_app";

  // Saving a value
  Serial.println("Saving configuration...");
  ConfigHelper::save(ns, "ssid", "MyWiFiNetwork");
  ConfigHelper::save(ns, "version", "2.1.0");
  ConfigHelper::save(ns, "interval", "300");

  // Reading values
  Serial.println("Reading configuration...");
  String ssid = ConfigHelper::read(ns, "ssid");
  String version = ConfigHelper::read(ns, "version");
  String interval = ConfigHelper::read(ns, "interval");

  Serial.println("SSID: " + ssid);
  Serial.println("Version: " + version);
  Serial.println("Interval: " + interval);

  // If a key doesn't exist, it returns an empty string
  String unknown = ConfigHelper::read(ns, "unknown_key");
  if (unknown == "") {
    Serial.println("Key 'unknown_key' not found.");
  }
}

void loop() {
  // Nothing to do here
}
