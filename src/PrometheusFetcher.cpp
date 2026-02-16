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

bool PrometheusFetcher::fetch(const String &url, const String &metric,
                              const String &labels, int debugLevel,
                              float &result) {
  String fullUrl = url + "?query=" + metric;
  if (!labels.isEmpty()) {
    fullUrl += "{" + labels + "}";
  }

  // Use the API version that returns the result in PrometheusResult
  PrometheusResult res;
  // Here we use divisor=1.0 and decimals=-1 to get raw value if possible
  // But wait, the existing fetch uses divisor and decimals.
  // We'll just call HttpClient directly or the other fetch and parse.

  if (debugLevel > 0) {
    Serial.print("[PromFetcher] Query: ");
    Serial.println(fullUrl);
  }

  if (fetch(fullUrl, 1.0, 2, res)) {
    result = res.value.toFloat();
    return true;
  }
  return false;
}
