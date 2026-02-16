#include <esp-iot-utils.h>

const char *ssid = "YOUR_SSID";
const char *password = "YOUR_PASSWORD";

// Example JSON API URL
// This API returns current time and some other info in JSON format
const char *api_url = "http://worldtimeapi.org/api/timezone/Europe/Paris";

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println("\n--- JsonFetcher Example ---");

  if (WiFiHelper::connect(ssid, password)) {
    JsonFetcherResult res;

    // JsonFetcher::fetch arguments:
    // 1. URL to fetch
    // 2. JSON path (e.g., "datetime" or "nested.field")
    // 3. Optional float filter (defaults to 1.0)
    // 4. Debug level (0: none, 1: error, 2: info)
    // 5. Result object to store the fetched value

    Serial.println("Fetching current time from API...");
    if (JsonFetcher::fetch(api_url, "datetime", 1.0, 1, res)) {
      Serial.print("Success! Fetched value: ");
      Serial.println(res.value);
    } else {
      Serial.println("Failed to fetch or parse JSON.");
    }
  }
}

void loop() {
  // Nothing to do here
}
