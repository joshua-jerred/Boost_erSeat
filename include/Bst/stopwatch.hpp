#ifndef STOPWATCH_HPP_
#define STOPWATCH_HPP_

#include "clock.hpp"
#include "exception.hpp"

namespace BoosterSeat {

enum class Resolution { SECONDS, MILLISECONDS, MICROSECONDS };

class Stopwatch {
 public:
  Stopwatch();
  ~Stopwatch() = default;

  enum class State { RUNNING, STOPPED };

  void start();
  void stop();
  void reset();

  State state() const;

  double elapsed(Resolution resolution = Resolution::SECONDS) const;

 private:
  clck::Clock clock_ = clck::Clock();
  clck::TimePoint start_ = clck::TimePoint::min();
  clck::TimePoint stop_time_ = clck::TimePoint::min();
  clck::Duration elapsed_ = clck::Duration::zero();
  State state_ = State::STOPPED;
};
}  // namespace BoosterSeat

#endif  // BOOST_ERSEAT_HPP_