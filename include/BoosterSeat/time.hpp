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

std::string timeString(TimeZone time_zone = TimeZone::LOCAL,
                       char delimiter = ':');

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