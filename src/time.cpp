#include <BoosterSeat/exception.hpp>
#include <BoosterSeat/time.hpp>

#include <algorithm>
#include <chrono>
#include <time.h>

#include <iostream> /// @todo remove

inline std::tm getTm(const bst::time::TimeZone time_zone, time_t time);
inline std::string timeFormatString(const char delimiter);
inline std::string dateFormatString(const char delimiter);

std::string
bst::time::elapsedAsciiClock(const bst::clck::TimePoint &time_point) {
  int seconds = bst::clck::secondsElapsed(time_point);
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

std::string bst::time::timeString(TimeZone time_zone, char delimiter,
                                  bst::clck::TimePoint time_point) {
  std::time_t time = bst::clck::toTimeT(time_point);
  std::tm tm = getTm(time_zone, time);
  std::stringstream ss;
  ss << std::put_time(&tm, timeFormatString(delimiter).c_str());
  return ss.str();
}

std::string bst::time::dateString(TimeZone time_zone, char delimiter) {
  auto time = std::time(nullptr);
  std::tm tm = getTm(time_zone, time);
  std::stringstream ss;
  ss << std::put_time(&tm, dateFormatString(delimiter).c_str());
  return ss.str();
}

std::string bst::time::dateAndTimeString(TimeZone time_zone,
                                         char date_delimiter,
                                         char between_delimiter,
                                         char time_delimiter,
                                         bst::clck::TimePoint time_point) {
  auto time = bst::clck::toTimeT(time_point);
  std::tm tm = getTm(time_zone, time);

  std::string format_string = dateFormatString(date_delimiter) +
                              std::string(1, between_delimiter) +
                              timeFormatString(time_delimiter);

  std::stringstream ss;
  ss << std::put_time(&tm, format_string.c_str());
  return ss.str();
}

bst::clck::TimePoint bst::time::dateAndTimeToTimePoint(int year, int month,
                                                       int day, int hour,
                                                       int minute, int second) {
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
    throw bst::BoosterSeatException("Invalid time",
                                    bst::ErrorNumber::TIME_INVALID_TIME);
  }

  return bst::clck::fromTimeT(time);
}

inline std::tm getTm(const bst::time::TimeZone time_zone, time_t time) {
  std::tm tm;
  switch (time_zone) {
  case bst::time::TimeZone::UTC:
    tm = *std::gmtime(&time);
    break;
  case bst::time::TimeZone::LOCAL:
    tm = *std::localtime(&time);
    break;
  default:
    throw bst::BoosterSeatException("Invalid time zone",
                                    bst::ErrorNumber::TIME_INVALID_TIMEZONE);
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

namespace bst {

uint32_t getUnixTime() {
  const auto clock = std::chrono::system_clock::now();
  return std::chrono::duration_cast<std::chrono::seconds>(
             clock.time_since_epoch())
      .count();
}

Time::Time(bool set_to_now) {
  if (set_to_now) {
    setToNow();
  }
}

void Time::setToNow() {
  time_ = std::time(nullptr);
}

std::string Time::toString() const {
  std::stringstream ss;
  ss << std::put_time(std::gmtime(&time_), "%Y-%m-%d %H:%M:%S");
  return ss.str();
}

bool Time::fromString(const std::string &time_string) {
  std::tm tm;
  std::stringstream ss(time_string);
  ss >> std::get_time(&tm, "%Y-%m-%d %H:%M:%S");
  if (ss.fail()) {
    return false;
  }

  // From <time.h>. This is not cross-platform!
  time_ = timegm(&tm);

  return true;
}

unsigned int Time::getYear() const {
  std::tm tm = *std::gmtime(&time_);
  return tm.tm_year + 1900;
}

unsigned int Time::getMonth() const {
  std::tm tm = *std::gmtime(&time_);
  return tm.tm_mon + 1;
}

unsigned int Time::getDay() const {
  std::tm tm = *std::gmtime(&time_);
  return tm.tm_mday;
}

unsigned int Time::getHour() const {
  std::tm tm = *std::gmtime(&time_);
  return tm.tm_hour;
}

unsigned int Time::getMinute() const {
  std::tm tm = *std::gmtime(&time_);
  return tm.tm_min;
}

unsigned int Time::getSecond() const {
  std::tm tm = *std::gmtime(&time_);
  return tm.tm_sec;
}

bool Time::operator<(const Time &rhs) const {
  return time_ < rhs.time_;
}

bool Time::operator>(const Time &rhs) const {
  return time_ > rhs.time_;
}

bool Time::operator<=(const Time &rhs) const {
  return time_ <= rhs.time_;
}

bool Time::operator>=(const Time &rhs) const {
  return time_ >= rhs.time_;
}

bool Time::operator==(const Time &rhs) const {
  return time_ == rhs.time_;
}

bool Time::operator!=(const Time &rhs) const {
  return time_ != rhs.time_;
}

int64_t Time::secondsFromNow() const {
  return std::difftime(time_, std::time(nullptr));
}

} // namespace bst