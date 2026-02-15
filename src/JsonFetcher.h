#ifndef JSON_FETCHER_H
#define JSON_FETCHER_H

#include <Arduino.h>
#include <ArduinoJson.h>

struct JsonFetcherResult {
  String value;
  bool success;
};

class JsonFetcher {
public:
  static bool fetch(const String &url, const String &jsonPath, float divisor,
                    int decimals, JsonFetcherResult &result);

private:
  static String extractValue(const String &json, const String &path);
};

#endif
