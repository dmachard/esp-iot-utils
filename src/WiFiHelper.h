#ifndef WIFI_HELPER_H
#define WIFI_HELPER_H

#include <Arduino.h>
#ifdef ESP32
#include <WiFi.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#endif

class WiFiHelper {
public:
  // Initialize and connect to WiFi with DNS configuration
  static bool connect(const String &ssid, const String &password,
                      const String &dnsMode = "auto",
                      const String &dnsPrimary = "",
                      const String &dnsSecondary = "");

  // Check if WiFi is connected
  static bool isConnected();

  // Get current IP address
  static String getIP();

  // Get DNS servers (for debugging)
  static String getDNS1();
  static String getDNS2();

  // Disconnect WiFi
  static void disconnect();

private:
  static bool configureDNS(const String &dnsMode, const String &dnsPrimary,
                           const String &dnsSecondary);
};

#endif // WIFI_HELPER_H
