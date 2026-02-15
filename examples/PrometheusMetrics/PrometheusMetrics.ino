#include <PrometheusFetcher.h>
#include <WiFiHelper.h>

const char *ssid = "YOUR_SSID";
const char *password = "YOUR_PASSWORD";

// Example Prometheus metrics endpoint
const char *metrics_url = "http://your-prometheus-exporter/metrics";

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println("\n--- PrometheusFetcher Example ---");

  if (WiFiHelper::connect(ssid, password)) {
    float value = 0.0;

    // PrometheusFetcher::fetch arguments:
    // 1. URL to fetch
    // 2. Metric name
    // 3. Labels (formatted as "label1=\"val1\",label2=\"val2\"")
    // 4. Debug level (0: none, 1: error, 2: info)
    // 5. Reference to float variable to store the result

    Serial.println("Fetching metric 'node_memory_MemAvailable_bytes'...");
    if (PrometheusFetcher::fetch(metrics_url, "node_memory_MemAvailable_bytes",
                                 "", 1, value)) {
      Serial.print("Available Memory: ");
      Serial.print(value / 1024 / 1024);
      Serial.println(" MB");
    }

    // Example with labels
    if (PrometheusFetcher::fetch(metrics_url, "up", "job=\"node\"", 1, value)) {
      Serial.print("Node exporter status: ");
      Serial.println(value == 1.0 ? "UP" : "DOWN");
    }
  }
}

void loop() {
  // Nothing to do here
}
