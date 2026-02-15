#include "PrometheusFetcher.h"
#include "HttpClient.h"
#include <ArduinoJson.h>

bool PrometheusFetcher::fetch(const String &url, float divisor, int decimals,
                              PrometheusResult &result) {
  if (url.isEmpty()) {
    Serial.println("[PromFetcher] ERROR: URL is empty");
    result.valid = false;
    return false;
  }

  Serial.print("[PromFetcher] Fetching: ");
  Serial.println(url);

  JsonDocument doc;

  if (!HttpClient::fetchJson(url, doc)) {
    Serial.println("[PromFetcher] Failed to fetch data");
    result.valid = false;
    return false;
  }

  // Parse Prometheus JSON: {"data": {"result": [{"value": [timestamp,
  // "value"]}]}}
  if (!doc["data"]["result"].is<JsonArray>() ||
      doc["data"]["result"].size() == 0) {
    Serial.println("[PromFetcher] No results in response");
    result.valid = false;
    return false;
  }

  float rawValue = doc["data"]["result"][0]["value"][1].as<float>();
  float convertedValue = rawValue / divisor;

  result.value = String(convertedValue, decimals);
  result.valid = true;

  Serial.print("[PromFetcher] Result: ");
  Serial.println(result.value);

  return true;
}
