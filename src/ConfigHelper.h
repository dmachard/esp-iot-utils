#ifndef CONFIG_HELPER_H
#define CONFIG_HELPER_H

#include <Arduino.h>
#include <ArduinoJson.h>
#include <Preferences.h>

class ConfigHelper {
public:
  void begin();
  void clear();

  // Static convenience methods (handle lifecycle internally)
  static void save(const char *ns, const char *key, String value);
  static void save(const char *ns, const char *key, int value);
  static String read(const char *ns, const char *key, String defaultValue = "");
  static int read(const char *ns, const char *key, int defaultValue);

  // Generic Getters/Setters (Overloaded)
  void set(const char *key, String value) { preferences.putString(key, value); }
  void set(const char *key, int value) { preferences.putInt(key, value); }
  void set(const char *key, long value) { preferences.putLong(key, value); }
  void set(const char *key, bool value) { preferences.putBool(key, value); }

  // Generic JSON Support
  void set(const char *key, JsonVariantConst value);
  void set(const char *key, JsonObjectConst value) {
    set(key, (JsonVariantConst)value);
  }
  void set(const char *key, JsonArrayConst value) {
    set(key, (JsonVariantConst)value);
  }
  bool get(const char *key, JsonDocument &doc);

  String get(const char *key, String defaultValue) {
    if (!preferences.isKey(key))
      return defaultValue;
    return preferences.getString(key, defaultValue);
  }
  int get(const char *key, int defaultValue) {
    if (!preferences.isKey(key))
      return defaultValue;
    return preferences.getInt(key, defaultValue);
  }
  long get(const char *key, long defaultValue) {
    if (!preferences.isKey(key))
      return defaultValue;
    return preferences.getLong(key, defaultValue);
  }
  bool get(const char *key, bool defaultValue) {
    if (!preferences.isKey(key))
      return defaultValue;
    return preferences.getBool(key, defaultValue);
  }

private:
  Preferences preferences;
};

#endif
