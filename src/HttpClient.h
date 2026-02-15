#ifndef HTTP_CLIENT_H
#define HTTP_CLIENT_H

#include <Arduino.h>
#include <ArduinoJson.h>
#ifdef ESP32
#include <HTTPClient.h>
#elif defined(ESP8266)
#include <ESP8266HTTPClient.h>
#endif

class HttpClient {
public:
  // Configuration
  static const int DEFAULT_TIMEOUT = 3000; // 3 seconds

  // Fetches JSON from a URL and parses it into a JsonDocument
  // Returns true if successful, false otherwise
  static bool fetchJson(const String &url, JsonDocument &doc,
                        int timeout = DEFAULT_TIMEOUT);

  // Generic GET that returns the body in response
  // Returns true if successful (code 200), false otherwise
  static bool get(const String &url, String &response,
                  int timeout = DEFAULT_TIMEOUT);

private:
  // Helper for error logging
  static void logError(const String &context, const String &error);
};

#endif // HTTP_CLIENT_H
