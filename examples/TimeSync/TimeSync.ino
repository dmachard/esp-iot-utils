#include <TimeHelper.h>
#include <WiFiHelper.h>

const char *ssid = "YOUR_SSID";
const char *password = "YOUR_PASSWORD";

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println("\n--- TimeHelper Example ---");

  if (WiFiHelper::connect(ssid, password)) {
    // Initialize NTP synchronization
    // Arguments: NTP Server, Timezone offset (seconds), Daylight offset
    // (seconds)
    Serial.println("Synchronizing time with NTP...");
    TimeHelper::setup("pool.ntp.org", 3600,
                      3600); // Example for CET (Central European Time)

    // Wait a bit for sync
    delay(2000);

    // Get formatted time strings
    Serial.print("Current Date: ");
    Serial.println(TimeHelper::getDate()); // returns "YYYY-MM-DD"

    Serial.print("Current Time: ");
    Serial.println(TimeHelper::getTime()); // returns "HH:MM:SS"

    Serial.print("Last Refresh: ");
    Serial.println(TimeHelper::getDatetimeShort()); // returns "HH:mm"
  }
}

void loop() {
  static unsigned long lastTick = 0;
  if (millis() - lastTick > 5000) {
    lastTick = millis();
    // Print time every 5 seconds
    Serial.println("Heartbeat: " + TimeHelper::getTime());
  }
}
