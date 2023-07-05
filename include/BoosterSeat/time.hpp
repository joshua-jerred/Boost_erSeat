#ifndef TIME_HPP_
#define TIME_HPP_

#include <BoosterSeat/clock.hpp>
#include <iomanip>
#include <sstream>
#include <string>

namespace BoosterSeat {
namespace time {

enum class TimeZone { UTC, LOCAL };

std::string elapsedAsciiClock(const BoosterSeat::clck::TimePoint &time_point);

/**
 * @brief Get the time in format: HH:MM:SS (24 hour clock) for a given time zone
 *
 * @param time_zone - The time zone to get the time in
 * @param delimiter - The delimiter to use (default: ':')
 * @param time - The time to get the string for (default: current time)
 * @return std::string - The time string
 */
std::string
timeString(TimeZone time_zone = TimeZone::LOCAL, char delimiter = ':',
           BoosterSeat::clck::TimePoint time_point = BoosterSeat::clck::now());

std::string dateString(TimeZone time_zone = TimeZone::LOCAL,
                       char delimiter = '-');

/**
 * @brief Get the date and time in the format: YYYY-MM-DD HH:MM:SS
 * @return std::string
 */
std::string dateAndTimeString(
    TimeZone time_zone = TimeZone::LOCAL, char date_delimiter = '-',
    char between_delimiter = ' ', char time_delimiter = ':',
    BoosterSeat::clck::TimePoint time_point = BoosterSeat::clck::now());

/**
 * @brief Convert a date and time to a BoosterSeat::clck::TimePoint
 * @details All parameters are clamped to their respective ranges.
 *
 * @param year - The year (e.g. 2023, must be greater than 1970)
 * @param month - The month (1 - 12)
 * @param day - The day (1 - 31)
 * @param hour - The hour (0 - 23)
 * @param minute - The minute (0 - 59)
 * @param second - The second (0 - 59)
 * @return BoosterSeat::clck::TimePoint - The time point
 */
BoosterSeat::clck::TimePoint dateAndTimeToTimePoint(int year, int month,
                                                    int day, int hour,
                                                    int minute, int second);

} // namespace time

} // namespace BoosterSeat

#endif // TIME_HPP_