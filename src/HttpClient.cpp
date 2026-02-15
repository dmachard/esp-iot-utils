#include "HttpClient.h"

bool HttpClient::get(const String &url, String &response, int timeout) {
  HTTPClient http;

  Serial.print("[HttpClient] GET: ");
  Serial.println(url);

  http.begin(url);
  http.setTimeout(timeout);

  int httpCode = http.GET();

  if (httpCode == HTTP_CODE_OK) {
    response = http.getString();
    http.end();
    Serial.println("[HttpClient] Success");
    return true;
  } else {
    logError("GET", "HTTP code: " + String(httpCode));
    http.end();
    return false;
  }
}

bool HttpClient::fetchJson(const String &url, JsonDocument &doc, int timeout) {
  String response;

  if (!get(url, response, timeout)) {
    return false;
  }

  DeserializationError error = deserializeJson(doc, response);

  if (error) {
    logError("fetchJson", "JSON parse error: " + String(error.c_str()));
    return false;
  }

  Serial.println("[HttpClient] JSON parsed successfully");
  return true;
}

void HttpClient::logError(const String &context, const String &error) {
  Serial.print("[HttpClient] ERROR in ");
  Serial.print(context);
  Serial.print(": ");
  Serial.println(error);
}
