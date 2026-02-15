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
};

#endif // PROMETHEUS_FETCHER_H
