#include "WiFiHelper.h"

bool WiFiHelper::configureDNS(const String &dnsMode, const String &dnsPrimary,
                              const String &dnsSecondary) {
  Serial.println("\n[DNS] Mode: " + dnsMode);

  if (dnsMode == "manual") {
    IPAddress primaryDns, secondaryDns;
    if (primaryDns.fromString(dnsPrimary) &&
        secondaryDns.fromString(dnsSecondary)) {

#ifdef ESP32
      WiFi.config(INADDR_NONE, INADDR_NONE, INADDR_NONE, primaryDns,
                  secondaryDns);
#elif defined(ESP8266)
      WiFi.config(WiFi.localIP(), WiFi.gatewayIP(), WiFi.subnetMask(),
                  primaryDns, secondaryDns);
#endif
      Serial.println("[DNS] Manual configured: " + dnsPrimary + ", " +
                     dnsSecondary);
      return true;
    } else {
      Serial.println("[DNS] Manual Config Error - using auto");
      return false;
    }
  } else {
    Serial.println("[DNS] Auto (from DHCP)");
    return true;
  }
}

bool WiFiHelper::connect(const String &ssid, const String &password,
                         const String &dnsMode, const String &dnsPrimary,
                         const String &dnsSecondary) {
  if (ssid.length() == 0) {
    Serial.println("[WiFi] No SSID configured");
    return false;
  }

  // Begin WiFi connection (get DHCP first)
  WiFi.begin(ssid.c_str(), password.c_str());
  Serial.print("[WiFi] Connecting to: " + ssid);

  // Wait for connection (max 10 seconds)
  int attempts = 0;
  while (WiFi.status() != WL_CONNECTED && attempts < 20) {
    delay(500);
    Serial.print(".");
    attempts++;
  }
  Serial.println();

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("[WiFi] Connected!");

    // Apply DNS AFTER connection (ESP32 requires this)
    if (dnsMode == "manual") {
      IPAddress primaryDns, secondaryDns;
      if (primaryDns.fromString(dnsPrimary) &&
          secondaryDns.fromString(dnsSecondary)) {
        // Reconfigure with same network settings but custom DNS
        WiFi.config(WiFi.localIP(), WiFi.gatewayIP(), WiFi.subnetMask(),
                    primaryDns, secondaryDns);
        Serial.println("[DNS] Manual set (post-connect): " + dnsPrimary + ", " +
                       dnsSecondary);
      } else {
        Serial.println("[DNS] Error - invalid DNS addresses");
      }
    } else {
      Serial.println("[DNS] Using DHCP DNS");
    }

    Serial.println("[WiFi] IP: " + WiFi.localIP().toString());
    Serial.println("[WiFi] Gateway: " + WiFi.gatewayIP().toString());
#ifdef ESP32
    Serial.println("[WiFi] DNS 1: " + WiFi.dnsIP(0).toString());
    Serial.println("[WiFi] DNS 2: " + WiFi.dnsIP(1).toString());
#elif defined(ESP8266)
    Serial.println("[WiFi] DNS: " + WiFi.dnsIP().toString());
#endif
    return true;
  } else {
    Serial.println("[WiFi] Connection failed");
    return false;
  }
}

bool WiFiHelper::isConnected() { return WiFi.status() == WL_CONNECTED; }

String WiFiHelper::getIP() { return WiFi.localIP().toString(); }

String WiFiHelper::getDNS1() {
#ifdef ESP32
  return WiFi.dnsIP(0).toString();
#elif defined(ESP8266)
  return WiFi.dnsIP().toString();
#else
  return "";
#endif
}

String WiFiHelper::getDNS2() {
#ifdef ESP32
  return WiFi.dnsIP(1).toString();
#else
  return "";
#endif
}

void WiFiHelper::disconnect() { WiFi.disconnect(); }
