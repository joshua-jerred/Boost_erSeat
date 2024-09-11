/**
 * @file stopwatch.hpp
 * @author Joshua Jerred (https://joshuajer.red)
 * @brief BoosterSeat Stopwatch class declaration
 * @date 2024-09-10
 * @copyright Copyright (c) 2024
 */

#ifndef STOPWATCH_HPP_
#define STOPWATCH_HPP_

#include "clock.hpp"
#include "exception.hpp"

namespace bst {

/// @brief A simple stopwatch class. Basic start (resume), stop (pause), and
/// reset functionality.
/// @tparam StopwatchClock - The clock to use for timing. Defaults to the
/// high_resolution_clock.
template <class StopwatchClock = clck::Clock>
class Stopwatch {
public:
  /// @brief Construct a new Stopwatch object. The stopwatch is stopped.
  Stopwatch() = default;

  /// @brief Default destructor
  ~Stopwatch() = default;

  /// @brief Start the stopwatch.
  /// @throw BoosterSeatException if the stopwatch is already running.
  void start() {
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

  /// @brief Stops/Pauses the stopwatch. Does *not* reset the elapsed time.
  void stop() {
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

  /// @brief Resets the elapsed time. The stopwatch will keep running by
  /// default.
  /// @param stop If true, the stopwatch will be stopped.
  void reset(bool stop = true) {
    elapsed_ = clck::Duration::zero();

    if (stop) {
      state_ = State::STOPPED;
    }
  }

  /// @brief Returns the current state of the stopwatch.
  bool isRunning() const {
    return state_ == State::RUNNING;
  }

  /// @brief The resolution/scale of the time returned by elapsed()
  enum class Scale { SECONDS, MILLISECONDS, MICROSECONDS };

  /// @brief Get the elapsed time in microseconds.
  int64_t elapsedMicroseconds() const {
    return std::chrono::duration_cast<clck::units::Microseconds>(getElapsed())
        .count();
  }
  /// @brief Get the elapsed time in microseconds in a floating point format.
  double elapsedMicrosecondsF() const {
    return std::chrono::duration_cast<clck::units::Microseconds>(getElapsed())
        .count();
  }

  /// @brief Get the elapsed time in milliseconds.
  int64_t elapsedMilliseconds() const {
    return std::chrono::duration_cast<clck::units::Milliseconds>(getElapsed())
        .count();
  }
  /// @brief Get the elapsed time in milliseconds in a floating point format.
  double elapsedMillisecondsF() const {
    return std::chrono::duration_cast<clck::units::Milliseconds>(getElapsed())
        .count();
  }

  /// @brief Get the elapsed time in seconds.
  int64_t elapsedSeconds() const {
    return std::chrono::duration_cast<clck::units::Seconds>(getElapsed())
        .count();
  }

  /// @brief Get the elapsed time in seconds in a floating point format.
  double elapsedSecondsF() const {
    return std::chrono::duration_cast<clck::units::Seconds>(getElapsed())
        .count();
  }

  //// -- Aliases

  /// @brief alias for stop() as it does what you want it to do.
  inline void pause() {
    stop();
  }

  /// @brief alias for start() as it does what you want it to do.
  inline void resume() {
    start();
  }

private:
  /// @brief Handles the timekeeping
  /// @return clck::Duration - The elapsed time
  bst::clck::Duration getElapsed() const {
    clck::Duration elapsed = elapsed_;
    if (state_ == State::RUNNING) {
      elapsed += clock_.now() - start_;
    }
    return elapsed;
  }

  /// @brief The state of the stopwatch
  enum class State { RUNNING, STOPPED };

  clck::Clock clock_;
  clck::TimePoint start_ = clck::TimePoint::min();
  clck::TimePoint stop_time_ = clck::TimePoint::min();
  clck::Duration elapsed_ = clck::Duration::zero();
  State state_ = State::STOPPED;
};
} // namespace bst

#endif // BOOST_ERSEAT_HPP_