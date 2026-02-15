#include "JsonFetcher.h"
#include "HttpClient.h"
#include <ArduinoJson.h>
#include <cmath>

bool JsonFetcher::fetch(const String &url, const String &jsonPath,
                        float divisor, int decimals,
                        JsonFetcherResult &result) {
  String payload;
  if (HttpClient::get(url, payload)) {
    String extractedValue = extractValue(payload, jsonPath);

    if (extractedValue == "null" || extractedValue.isEmpty()) {
      result.value = "ERR";
      result.success = false;
      return false;
    }

    // Try to convert to float for formatting
    float value = extractedValue.toFloat();
    if (value == 0.0 && extractedValue != "0" && extractedValue != "0.0") {
      // value is likely string, just return it ?
      // For now, we assume we want numbers as we have divisor/decimals
      // But if it fails to parse, maybe we just return the string?
      // The struct has 'value' as String.
      // Let's assume numeric processing is desired if divisor != 1
    }

    if (divisor != 1.0) {
      value = value / divisor;
    }

    if (decimals >= 0) {
      result.value = String(value, decimals);
    } else {
      result.value = extractedValue;
    }

    result.success = true;
    return true;
  } else {
    Serial.println("[JsonFetcher] Failed to fetch URL");
    result.value = "ERR";
    result.success = false;
    return false;
  }
}

String JsonFetcher::extractValue(const String &json, const String &path) {
  JsonDocument doc;
  DeserializationError error = deserializeJson(doc, json);

  if (error) {
    Serial.print("[JsonFetcher] deserializeJson() failed: ");
    Serial.println(error.c_str());
    return "null";
  }

  JsonVariant current = doc.as<JsonVariant>();
  String currentPath = path;

  // Simple parser for dot notation and array brackets
  // e.g. "data.sensors[0].value"
  int pos = 0;
  while (pos < currentPath.length()) {
    int dotPos = currentPath.indexOf('.', pos);
    int bracketPos = currentPath.indexOf('[', pos);

    int nextSep = -1;
    if (dotPos != -1 && bracketPos != -1)
      nextSep = std::min(dotPos, bracketPos);
    else if (dotPos != -1)
      nextSep = dotPos;
    else if (bracketPos != -1)
      nextSep = bracketPos;
    else
      nextSep = currentPath.length();

    String key = currentPath.substring(pos, nextSep);

    if (!key.isEmpty()) {
      if (current.is<JsonObject>()) {
        current = current[key];
      } else {
        return "null";
      }
    }

    if (nextSep == currentPath.length())
      break;

    if (currentPath[nextSep] == '.') {
      pos = nextSep + 1;
    } else if (currentPath[nextSep] == '[') {
      int closeBracket = currentPath.indexOf(']', nextSep);
      if (closeBracket == -1)
        return "null"; // Malformed
      String indexStr = currentPath.substring(nextSep + 1, closeBracket);
      int index = indexStr.toInt();
      if (current.is<JsonArray>()) {
        current = current[index];
      } else {
        return "null";
      }
      pos = closeBracket + 1;
      // Handle optional dot after bracket like [0].value
      if (pos < currentPath.length() && currentPath[pos] == '.') {
        pos++;
      }
    }
  }

  if (current.isNull())
    return "null";
  return current.as<String>();
}
