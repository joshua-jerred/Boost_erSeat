#ifndef TIME_HPP_
#define TIME_HPP_

#include <chrono>

namespace BoosterSeat {
namespace time {
typedef std::chrono::high_resolution_clock Clock;
typedef std::chrono::time_point<Clock> TimePoint;
typedef Clock::duration Duration;

namespace units {
typedef std::chrono::duration<double, std::ratio<1, 1>> Seconds;
typedef std::chrono::duration<double, std::ratio<1, 1000>> Milliseconds;
typedef std::chrono::duration<double, std::ratio<1, 1000000>> Microseconds;
}  // namespace units
}  // namespace time
}  // namespace BoosterSeat

#endif  // TIME_HPP_