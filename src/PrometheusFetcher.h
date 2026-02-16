#ifndef PROMETHEUS_FETCHER_H
#define PROMETHEUS_FETCHER_H

#include <Arduino.h>

struct PrometheusResult {
  String value;
  bool valid;

  PrometheusResult() : value("--"), valid(false) {}
};

class PrometheusFetcher {
public:
  static bool fetch(const String &url, float divisor, int decimals,
                    PrometheusResult &result);

  // Overload for building query URL (matching PrometheusMetrics example)
  // url: base API URL (e.g. http://prom:9090/api/v1/query)
  static bool fetch(const String &url, const String &metric,
                    const String &labels, int debugLevel, float &result);
};

#endif // PROMETHEUS_FETCHER_H
