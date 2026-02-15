#ifdef ESP32
#include "ConfigHelper.h"
#include <ArduinoJson.h>

void ConfigHelper::begin() { preferences.begin("config", false); }

void ConfigHelper::clear() { preferences.clear(); }

void ConfigHelper::set(const char *key, JsonVariantConst value) {
  String json;
  serializeJson(value, json);
  set(key, json);
}

bool ConfigHelper::get(const char *key, JsonDocument &doc) {
  String json = get(key, String(""));
  if (json.isEmpty())
    return false;

  DeserializationError error = deserializeJson(doc, json);
  return !error;
}
#endif
