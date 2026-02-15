#include "UrlHelper.h"
#include "TimeHelper.h"

String UrlHelper::replaceDatePlaceholders(String url) {
  if (url.indexOf("{date}") == -1 && url.indexOf("%DATE%") == -1) {
    return url;
  }

  String today = TimeHelper::getTodayDate();
  if (today == "1970-01-01") {
    Serial.println(
        "[UrlHelper] Warning: Time not synchronized, using default date");
  }

  String finalUrl = url;
  finalUrl.replace("{date}", today);
  finalUrl.replace("%DATE%", today);
  return finalUrl;
}
