#include <BoosterSeat/timer.hpp>

namespace bst {

Timer::Timer(int timeout_ms) : timeout_ms_(timeout_ms) {
  if (timeout_ms < 0) {
    throw bst::BoosterSeatException("Time must be non-negative");
  }
}

Timer::Timer() : timeout_ms_(0) {
}

void Timer::reset() {
  start_ = bst::clck::Clock::now();
}

bool Timer::isDone() const {
  return (bst::clck::Clock::now() - start_) >=
         bst::clck::units::Milliseconds(timeout_ms_);
}

void Timer::setTimeout(int timeout_ms) {
  if (timeout_ms < 0) {
    throw bst::BoosterSeatException("Time must be non-negative");
  }
  timeout_ms_ = timeout_ms;
}

void Timer::setDone() {
  start_ = bst::clck::Clock::now() - std::chrono::milliseconds(timeout_ms_);
}

} // namespace bst