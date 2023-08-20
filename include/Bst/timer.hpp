#ifndef TIMER_HPP_
#define TIMER_HPP_

#include <Bst/clock.hpp>
#include <Bst/exception.hpp>

namespace BoosterSeat {
class Timer {
public:
  Timer(int timeout_ms);
  Timer(); // default to 0
  ~Timer() = default;

  void reset();
  bool isDone() const;
  void setTimeout(int timeout_ms);

private:
  clck::TimePoint start_ = clck::Clock::now();
  int timeout_ms_;
};
} // namespace BoosterSeat

#endif /* TIMER_HPP_ */