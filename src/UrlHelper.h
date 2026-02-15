#ifndef URL_HELPER_H
#define URL_HELPER_H

#include <Arduino.h>

class UrlHelper {
public:
  /**
   * Replaces {date} and %DATE% placeholders in a URL with the current date
   * (YYYY-MM-DD). Requires TimeHelper to be initialized and synchronized.
   */
  static String replaceDatePlaceholders(String url);
};

#endif // URL_HELPER_H
