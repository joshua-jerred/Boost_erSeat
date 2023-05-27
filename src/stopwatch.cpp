#include "BoosterSeat/stopwatch.hpp"

using namespace BoosterSeat;

Stopwatch::Stopwatch() {
  state_ = State::STOPPED;
}

void Stopwatch::start() {
  if (state_ == State::STOPPED) {
    start_ = clock_.now();
    state_ = State::RUNNING;
  }

  #ifndef BOOSTERSEAT_NO_EXCEPTION
  else {
    throw BoosterSeatException("Stopwatch is already running.");
  }
  #endif
}

void Stopwatch::stop() {
  if (state_ == State::RUNNING) {
    stop_time_ = clock_.now();
    elapsed_ += stop_time_ - start_;
    state_ = State::STOPPED;
  }

  #ifndef BOOSTERSEAT_NO_EXCEPTION
  else {
    throw BoosterSeatException("Stopwatch is not running.");
  }
  #endif
}

void Stopwatch::reset() {
  elapsed_ = clck::Duration::zero();
  state_ = State::STOPPED;
}

Stopwatch::State Stopwatch::state() const {
  return state_;
}

double Stopwatch::elapsed(Resolution resolution) const {
  double elapsed = 0.0;
  switch (resolution) {
    case Resolution::SECONDS:
      elapsed = std::chrono::duration_cast<clck::units::Seconds>(elapsed_).count();
      break;
    case Resolution::MILLISECONDS:
      elapsed =
          std::chrono::duration_cast<clck::units::Milliseconds>(elapsed_).count();
      break;
    case Resolution::MICROSECONDS:
      elapsed =
          std::chrono::duration_cast<clck::units::Microseconds>(elapsed_).count();
      break;
  }
  return elapsed;
}