#include "TimeHelper.h"

bool TimeHelper::initialized = false;
const char *TimeHelper::_ntpServer = nullptr;
long TimeHelper::_gmtOffset = 0;
int TimeHelper::_daylightOffset = 0;
String TimeHelper::_language = "en";

// French locale constants
const char *TimeHelper::DAYS_FR[] = {
    "DIMANCHE", "LUNDI", "MARDI", "MERCREDI", "JEUDI", "VENDREDI", "SAMEDI"};

const char *TimeHelper::MONTHS_FR[] = {
    "JANVIER", "FÉVRIER", "MARS",      "AVRIL",   "MAI",      "JUIN",
    "JUILLET", "AOÛT",    "SEPTEMBRE", "OCTOBRE", "NOVEMBRE", "DÉCEMBRE"};

// English locale constants
const char *TimeHelper::DAYS_EN[] = {"SUNDAY",    "MONDAY",   "TUESDAY",
                                     "WEDNESDAY", "THURSDAY", "FRIDAY",
                                     "SATURDAY"};

const char *TimeHelper::MONTHS_EN[] = {
    "JANUARY", "FEBRUARY", "MARCH",     "APRIL",   "MAY",      "JUNE",
    "JULY",    "AUGUST",   "SEPTEMBER", "OCTOBER", "NOVEMBER", "DECEMBER"};

void TimeHelper::init(const char *ntpServer, long gmtOffset,
                      int daylightOffset) {
  if (initialized)
    return;

  _ntpServer = ntpServer;
  _gmtOffset = gmtOffset;
  _daylightOffset = daylightOffset;

  configTime(gmtOffset, daylightOffset, ntpServer);
  initialized = true;

  Serial.println("[TimeHelper] NTP configured");
}

void TimeHelper::setLanguage(String lang) {
  _language = lang;
  Serial.println("[TimeHelper] Language set to: " + _language);
}

String TimeHelper::getLanguage() { return _language; }

bool TimeHelper::getLocalTime(struct tm *info) {
  time_t now = time(nullptr);
  if (now < 8 * 3600 * 2) { // Non-synced time check
    return false;
  }
  struct tm *timeinfo = localtime(&now);
  if (timeinfo == nullptr) {
    return false;
  }
  *info = *timeinfo;
  return true;
}

String TimeHelper::getTodayDate() {
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    return "";
  }

  char buffer[11];
  snprintf(buffer, sizeof(buffer), "%04d-%02d-%02d", 1900 + timeinfo.tm_year,
           timeinfo.tm_mon + 1, timeinfo.tm_mday);
  return String(buffer);
}

String TimeHelper::getTime() {
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    return "";
  }
  char buffer[9];
  snprintf(buffer, sizeof(buffer), "%02d:%02d:%02d", timeinfo.tm_hour,
           timeinfo.tm_min, timeinfo.tm_sec);
  return String(buffer);
}

String TimeHelper::getDatetimeShort() {
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    return "";
  }
  char buffer[6];
  snprintf(buffer, sizeof(buffer), "%02d:%02d", timeinfo.tm_hour,
           timeinfo.tm_min);
  return String(buffer);
}

const char *TimeHelper::getDayName(int dayOfWeek) {
  if (dayOfWeek < 0 || dayOfWeek > 6)
    return "";

  if (_language == "fr") {
    return DAYS_FR[dayOfWeek];
  }
  return DAYS_EN[dayOfWeek];
}

const char *TimeHelper::getMonthName(int month) {
  if (month < 0 || month > 11)
    return "";

  if (_language == "fr") {
    return MONTHS_FR[month];
  }
  return MONTHS_EN[month];
}

int TimeHelper::getISOWeekNumber(const struct tm &timeinfo) {
  int dayOfYear = timeinfo.tm_yday + 1;
  return (dayOfYear / 7) + 1;
}
