#include <BoosterSeat/exception.hpp>
#include <BoosterSeat/time.hpp>

#include <algorithm>

inline std::tm getTm(const BoosterSeat::time::TimeZone time_zone, time_t time);
inline std::string timeFormatString(const char delimiter);
inline std::string dateFormatString(const char delimiter);

std::string BoosterSeat::time::elapsedAsciiClock(
    const BoosterSeat::clck::TimePoint &time_point) {
  int seconds = BoosterSeat::clck::secondsElapsed(time_point);
  int minutes = seconds / 60;
  int hours = minutes / 60;
  seconds %= 60;
  minutes %= 60;

  std::string seconds_str = std::to_string(seconds);
  std::string minutes_str = std::to_string(minutes);
  std::string hours_str = std::to_string(hours);

  if (seconds < 10) {
    seconds_str = "0" + seconds_str;
  }
  if (minutes < 10) {
    minutes_str = "0" + minutes_str;
  }
  if (hours < 10) {
    hours_str = "0" + hours_str;
  }

  return hours_str + ":" + minutes_str + ":" + seconds_str;
}

std::string
BoosterSeat::time::timeString(TimeZone time_zone, char delimiter,
                              BoosterSeat::clck::TimePoint time_point) {
  std::time_t time = BoosterSeat::clck::toTimeT(time_point);
  std::tm tm = getTm(time_zone, time);
  std::stringstream ss;
  ss << std::put_time(&tm, timeFormatString(delimiter).c_str());
  return ss.str();
}

std::string BoosterSeat::time::dateString(TimeZone time_zone, char delimiter) {
  auto time = std::time(nullptr);
  std::tm tm = getTm(time_zone, time);
  std::stringstream ss;
  ss << std::put_time(&tm, dateFormatString(delimiter).c_str());
  return ss.str();
}

std::string BoosterSeat::time::dateAndTimeString(
    TimeZone time_zone, char date_delimiter, char between_delimiter,
    char time_delimiter, BoosterSeat::clck::TimePoint time_point) {
  auto time = BoosterSeat::clck::toTimeT(time_point);
  std::tm tm = getTm(time_zone, time);

  std::string format_string = dateFormatString(date_delimiter) +
                              std::string(1, between_delimiter) +
                              timeFormatString(time_delimiter);

  std::stringstream ss;
  ss << std::put_time(&tm, format_string.c_str());
  return ss.str();
}

BoosterSeat::clck::TimePoint
BoosterSeat::time::dateAndTimeToTimePoint(int year, int month, int day,
                                          int hour, int minute, int second) {
  std::tm tm;
  tm.tm_year = std::clamp(year - 1900, 0, 9999);
  tm.tm_mon = std::clamp(month - 1, 0, 11);
  tm.tm_mday = std::clamp(day, 1, 31);
  tm.tm_hour = std::clamp(hour, 0, 23);
  tm.tm_min = std::clamp(minute, 0, 59);
  tm.tm_sec = std::clamp(second, 0, 59);
  tm.tm_isdst = -1; // no information about daylight saving time

  std::time_t time = std::mktime(&tm);
  if (time == -1) {
    throw BoosterSeat::BoosterSeatException(
        "Invalid time", BoosterSeat::ErrorNumber::TIME_INVALID_TIME);
  }

  return BoosterSeat::clck::fromTimeT(time);
}

inline std::tm getTm(const BoosterSeat::time::TimeZone time_zone, time_t time) {
  std::tm tm;
  switch (time_zone) {
  case BoosterSeat::time::TimeZone::UTC:
    tm = *std::gmtime(&time);
    break;
  case BoosterSeat::time::TimeZone::LOCAL:
    tm = *std::localtime(&time);
    break;
  default:
    throw BoosterSeat::BoosterSeatException(
        "Invalid time zone", BoosterSeat::ErrorNumber::TIME_INVALID_TIMEZONE);
  }
  return tm;
}

inline std::string timeFormatString(const char delimiter) {
  std::string format_string;
  if (delimiter == '\0') {
    format_string = "%H%M%S";
  } else {
    format_string = "%H" + std::string(1, delimiter) + "%M" +
                    std::string(1, delimiter) + "%S";
  }
  return format_string;
}

inline std::string dateFormatString(const char delimiter) {
  std::string format_string;
  if (delimiter == '\0') {
    format_string = "%Y%m%d";
  } else {
    format_string = "%Y" + std::string(1, delimiter) + "%m" +
                    std::string(1, delimiter) + "%d";
  }
  return format_string;
}