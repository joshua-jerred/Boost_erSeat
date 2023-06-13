#ifndef TIMER_HPP_
#define TIMER_HPP_

#include <BoosterSeat/clock.hpp>
#include <BoosterSeat/exception.hpp>

namespace BoosterSeat {
class Timer {
public:
  Timer(int timeout_ms);
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