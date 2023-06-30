#ifndef CLOCK_HPP_
#define CLOCK_HPP_

#include <chrono>

namespace BoosterSeat {
namespace clck {

namespace units {
typedef std::chrono::duration<double, std::ratio<1, 1>> Seconds;
typedef std::chrono::duration<double, std::ratio<1, 1000>> Milliseconds;
typedef std::chrono::duration<double, std::ratio<1, 1000000>> Microseconds;
} // namespace units

typedef std::chrono::high_resolution_clock Clock;
typedef std::chrono::time_point<Clock> TimePoint;
typedef Clock::duration Duration;

inline TimePoint now() {
  return clck::Clock::now();
}

inline int secondsElapsed(const TimePoint &time_point) {
  return std::chrono::duration_cast<units::Seconds>(clck::now() - time_point)
      .count();
}

inline int millisecondsElapsed(const TimePoint &time_point) {
  return std::chrono::duration_cast<units::Milliseconds>(now() - time_point)
      .count();
}

inline time_t toTimeT(const TimePoint &time_point) {
  return Clock::to_time_t(time_point);
}

} // namespace clck
} // namespace BoosterSeat

#endif