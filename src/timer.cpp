#include <BoosterSeat/timer.hpp>

using namespace BoosterSeat;

Timer::Timer(int timeout_ms) : timeout_ms_(timeout_ms) {
  if (timeout_ms < 0) {
    throw BoosterSeatException("Time must be non-negative");
  }
}

void Timer::reset() {
  start_ = clck::Clock::now();
}

bool Timer::isDone() {
  return (clck::Clock::now() - start_) >=
         clck::units::Milliseconds(timeout_ms_);
}

void Timer::setTimeout(int timeout_ms) {
  if (timeout_ms < 0) {
    throw BoosterSeatException("Time must be non-negative");
  }
  timeout_ms_ = timeout_ms;
}
