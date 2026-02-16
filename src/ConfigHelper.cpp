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

void ConfigHelper::save(const char *ns, const char *key, String value) {
  Preferences p;
  p.begin(ns, false);
  p.putString(key, value);
  p.end();
}

void ConfigHelper::save(const char *ns, const char *key, int value) {
  Preferences p;
  p.begin(ns, false);
  p.putInt(key, value);
  p.end();
}

String ConfigHelper::read(const char *ns, const char *key,
                          String defaultValue) {
  Preferences p;
  p.begin(ns, true);
  String val = p.getString(key, defaultValue);
  p.end();
  return val;
}

int ConfigHelper::read(const char *ns, const char *key, int defaultValue) {
  Preferences p;
  p.begin(ns, true);
  int val = p.getInt(key, defaultValue);
  p.end();
  return val;
}
#endif
