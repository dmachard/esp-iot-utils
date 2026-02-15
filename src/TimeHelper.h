#ifndef TIME_HELPER_H
#define TIME_HELPER_H

#include <Arduino.h>
#include <time.h>

class TimeHelper {
public:
  static void init(const char *ntpServer, long gmtOffset, int daylightOffset);
  static bool getLocalTime(struct tm *info);
  static String getTodayDate(); // Returns YYYY-MM-DD

  // Locale support
  static void setLanguage(String lang);
  static String getLanguage();
  static const char *getDayName(int dayOfWeek); // 0=Sunday, 6=Saturday
  static const char *getMonthName(int month);   // 0=January, 11=December
  static int getISOWeekNumber(const struct tm &timeinfo);

private:
  static bool initialized;
  static const char *_ntpServer;
  static long _gmtOffset;
  static int _daylightOffset;
  static String _language;

  // Day and month names
  static const char *DAYS_FR[];
  static const char *MONTHS_FR[];
  static const char *DAYS_EN[];
  static const char *MONTHS_EN[];
};

#endif
