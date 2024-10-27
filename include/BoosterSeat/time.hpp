#ifndef TIME_HPP_
#define TIME_HPP_

#include <BoosterSeat/clock.hpp>
#include <iomanip>
#include <sstream>
#include <string>

namespace bst {

/// @deprecated The time namespace will be removed in the future.
namespace time {

enum class TimeZone { UTC, LOCAL };

std::string elapsedAsciiClock(const bst::clck::TimePoint &time_point);

/**
 * @brief Get the time in format: HH:MM:SS (24 hour clock) for a given time zone
 *
 * @param time_zone - The time zone to get the time in
 * @param delimiter - The delimiter to use (default: ':')
 * @param time - The time to get the string for (default: current time)
 * @return std::string - The time string
 */
std::string timeString(TimeZone time_zone = TimeZone::LOCAL,
                       char delimiter = ':',
                       bst::clck::TimePoint time_point = bst::clck::now());

std::string dateString(TimeZone time_zone = TimeZone::LOCAL,
                       char delimiter = '-');

/**
 * @brief Get the date and time in the format: YYYY-MM-DD HH:MM:SS
 * @return std::string
 */
std::string
dateAndTimeString(TimeZone time_zone = TimeZone::LOCAL,
                  char date_delimiter = '-', char between_delimiter = ' ',
                  char time_delimiter = ':',
                  bst::clck::TimePoint time_point = bst::clck::now());

inline std::string dateAndTimeString(const bst::clck::TimePoint &time_point) {
  return dateAndTimeString(TimeZone::LOCAL, '-', ' ', ':', time_point);
}

/**
 * @brief Convert a date and time to a bst::clck::TimePoint
 * @details All parameters are clamped to their respective ranges.
 *
 * @param year - The year (e.g. 2023, must be greater than 1970)
 * @param month - The month (1 - 12)
 * @param day - The day (1 - 31)
 * @param hour - The hour (0 - 23)
 * @param minute - The minute (0 - 59)
 * @param second - The second (0 - 59)
 * @return bst::clck::TimePoint - The time point
 */
bst::clck::TimePoint dateAndTimeToTimePoint(int year, int month, int day,
                                            int hour, int minute, int second);

} // namespace time

} // namespace bst

namespace bst {

/// @brief Get the current Unix time
/// @return The current Unix time in seconds (seconds since epoch)
uint32_t getUnixTime();

/**
 * @brief The generic time class for BoosterSeat. Uses UTC time.
 *
 * @warning This class has many issues related to time zones and DST. It's
 * current purpose is just for simple time saving/loading in the giraffe
 * project. This needs some serious work and testing before it can be used.
 */
class Time {
public:
  /**
   * @brief Construct a new Time object. Defaults to the epoch.
   * @param set_to_now - Set the time to the current time. Defaults to false.
   */
  Time(bool set_to_now = false);
  ~Time() = default;

  // operators
  bool operator==(const Time &rhs) const;
  bool operator!=(const Time &rhs) const;
  bool operator<(const Time &rhs) const;
  bool operator<=(const Time &rhs) const;
  bool operator>(const Time &rhs) const;
  bool operator>=(const Time &rhs) const;

  /**
   * @brief Set the time to the current time
   */
  void setToNow();

  /**
   * @brief Get the time/date as a string in the format: YYYY-MM-DD HH:MM:SS
   * @return std::string - The time/date string
   */
  std::string toString() const;

  /**
   * @brief
   * @warning This function is *not* cross platform. It will work on Linux.
   *
   * @param time_string - The time string to parse in the format: YYYY-MM-DD
   * HH:MM:SS
   * @return true - The time string was parsed successfully
   * @return false - The time string was not parsed successfully
   */
  bool fromString(const std::string &time_string);

  /**
   * @brief Get the Year
   * @return unsigned int - The year
   */
  unsigned int getYear() const;

  /**
   * @brief Get the Month (1 - 12)
   * @return unsigned int - The month
   */
  unsigned int getMonth() const;

  /**
   * @brief Get the Day
   * @return unsigned int - The day
   */
  unsigned int getDay() const;

  /**
   * @brief Get the Hour
   * @return unsigned int - The hour
   */
  unsigned int getHour() const;

  /**
   * @brief Get the Minute
   * @return unsigned int - The minute
   */
  unsigned int getMinute() const;

  /**
   * @brief Get the Second
   * @return unsigned int - The second
   */
  unsigned int getSecond() const;

  time_t getTimeType() const {
    return time_;
  }

  /**
   * @brief Returns the number of seconds from the current time to the stored
   * time.
   * @return int32_t Number of seconds from the current time. Negative if the
   * stored time is in the past. Positive if the stored time is in the future.
   */
  int64_t secondsFromNow() const;

private:
  time_t time_ = 0;
};

} // namespace bst

#endif // TIME_HPP_