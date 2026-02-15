# esp-iot-utils

**A collection of utility classes for ESP32 and ESP8266 projects.**

esp-iot-utils is a sober and descriptive library that gathers essential tools for IoT projects. It helps avoid code repetition for networking, data fetching, and system management.

## Features

- **HttpClient**: Simplified HTTP(S) requests (Cross-platform ESP32/ESP8266).
- **JsonFetcher**: Quick value extraction from JSON APIs using path strings.
- **PrometheusFetcher**: Parse Prometheus metrics with ease.
- **UrlHelper**: Replace date placeholders in URLs automatically.
- **WiFiHelper**: Robust cross-platform WiFi connection management.
- **TimeHelper**: Easy NTP synchronization and date formatting.
- **ConfigHelper**: Simple configuration storage (Uses Preferences on ESP32).

## Compatibility

- ✅ **ESP32** (All variants)
- ✅ **ESP8266** (Partial support for ConfigHelper)
- ✅ **PlatformIO** & **Arduino IDE**

## Installation

### PlatformIO
Add the following to your `platformio.ini`:
```ini
lib_deps =
    denis/esp-iot-utils
    bblanchon/ArduinoJson @ ^7.0.0
```

### Arduino IDE
Download this repository as a ZIP and add it to your libraries. Manually install **ArduinoJson** version 7+ via the Library Manager.

## Usage Sample

You can include the individual headers you need, or the primary header for convenience:

```cpp
#include <esp-iot-utils.h>

void setup() {
    Serial.begin(115200);
    if (WiFiHelper::connect("SSID", "PASS")) {
        JsonFetcherResult res;
        // Fetch a value from a JSON API
        if (JsonFetcher::fetch("http://my-api.com/status", "sensor.value", 1.0, 1, res)) {
            Serial.println("Value: " + res.value);
        }
    }
}
```

## Examples

Several examples are available in the [examples](examples/) folder to help you get started:

- **[WiFiConnection](examples/WifiConnection/WiFiConnection.ino)**: How to connect to WiFi.
- **[JsonFetching](examples/JsonFetching/JsonFetching.ino)**: Extracting data from JSON APIs.
- **[TimeSync](examples/TimeSync/TimeSync.ino)**: NTP synchronization and date formatting.
- **[ConfigStorage](examples/ConfigStorage/ConfigStorage.ino)**: Persistent configuration storage.
- **[PrometheusMetrics](examples/PrometheusMetrics/PrometheusMetrics.ino)**: Parsing Prometheus metrics.

## License
MIT
