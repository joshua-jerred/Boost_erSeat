#ifndef TIME_HPP_
#define TIME_HPP_

#include <BoosterSeat/clock.hpp>
#include <iomanip>
#include <sstream>
#include <string>

namespace BoosterSeat {
namespace time {

std::string utcTimeString();
std::string localTimeString();
std::string getDateAndTimeStr();

std::string elapsedAsciiClock(const BoosterSeat::clck::TimePoint &time_point);

}  // namespace time
}  // namespace BoosterSeat

#endif  // TIME_HPP_