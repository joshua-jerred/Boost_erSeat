#include <BoosterSeat/exception.hpp>
#include <BoosterSeat/time.hpp>

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

std::string BoosterSeat::time::timeString(TimeZone time_zone, char delimiter,
                                          time_t time) {
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

std::string BoosterSeat::time::dateAndTimeString(TimeZone time_zone,
                                                 char date_delimiter,
                                                 char between_delimiter,
                                                 char time_delimiter) {
  auto time = std::time(nullptr);
  std::tm tm = getTm(time_zone, time);

  std::string format_string = dateFormatString(date_delimiter) +
                              std::string(1, between_delimiter) +
                              timeFormatString(time_delimiter);

  std::stringstream ss;
  ss << std::put_time(&tm, format_string.c_str());
  return ss.str();
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