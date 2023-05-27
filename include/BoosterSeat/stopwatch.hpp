#ifndef STOPWATCH_HPP_
#define STOPWATCH_HPP_

#include "time.hpp"
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
  time::Clock clock_ = time::Clock();
  time::TimePoint start_ = time::TimePoint::min();
  time::TimePoint stop_time_ = time::TimePoint::min();
  time::Duration elapsed_ = time::Duration::zero();
  State state_ = State::STOPPED;
};
}  // namespace BoosterSeat

#endif  // BOOST_ERSEAT_HPP_