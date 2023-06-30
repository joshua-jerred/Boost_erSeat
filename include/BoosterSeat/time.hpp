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
std::string dateAndTimeString(TimeZone time_zone = TimeZone::LOCAL,
                              char date_delimiter = '-',
                              char between_delimiter = ' ',
                              char time_delimiter = ':');

} // namespace time
} // namespace BoosterSeat

#endif // TIME_HPP_