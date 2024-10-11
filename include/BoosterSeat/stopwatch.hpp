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

class IStopwatch {
public:
  virtual void start() = 0;
  virtual void stop() = 0;
  virtual void reset(bool stop = true) = 0;
  virtual bool isRunning() const = 0;
  virtual int64_t elapsedMicroseconds() const = 0;
  virtual double elapsedMicrosecondsF() const = 0;
  virtual int64_t elapsedMilliseconds() const = 0;
  virtual double elapsedMillisecondsF() const = 0;
  virtual int64_t elapsedSeconds() const = 0;
  virtual double elapsedSecondsF() const = 0;
  virtual void pause() = 0;
  virtual void resume() = 0;
  virtual ~IStopwatch() = default;

protected:
  /// @brief The state of the stopwatch
  enum class State { RUNNING, STOPPED };

  /// @brief The state of the stopwatch
  State state_ = State::STOPPED;
};

/// @brief A simple stopwatch class. Basic start (resume), stop (pause), and
/// reset functionality.
class Stopwatch : public IStopwatch {
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
    start_ = clock_.now();

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

protected:
  /// @brief Handles the timekeeping
  /// @return clck::Duration - The elapsed time
  bst::clck::Duration getElapsed() const {
    clck::Duration elapsed = elapsed_;
    if (state_ == State::RUNNING) {
      elapsed += clock_.now() - start_;
    }
    return elapsed;
  }

private:
  clck::Clock clock_;
  clck::TimePoint start_ = clck::TimePoint::min();
  clck::TimePoint stop_time_ = clck::TimePoint::min();
  clck::Duration elapsed_ = clck::Duration::zero();
  State state_ = State::STOPPED;
};

/// @brief A manually controlled stopwatch that does not use the system clock.
class SoftwareStopwatch : public IStopwatch {
public:
  SoftwareStopwatch() = default;
  ~SoftwareStopwatch() = default;

  void start() {
    if (state_ == State::STOPPED) {
      start_ = 0;
      state_ = State::RUNNING;
    }
#ifndef BOOSTERSEAT_NO_EXCEPTION
    else {
      throw BoosterSeatException("Stopwatch is already running.");
    }
#endif
  }

  void stop() {
    if (state_ == State::RUNNING) {
      stop_time_ = 0;
      elapsed_ += stop_time_ - start_;
      state_ = State::STOPPED;
    }
#ifndef BOOSTERSEAT_NO_EXCEPTION
    else {
      throw BoosterSeatException("Stopwatch is not running.");
    }
#endif
  }

  void reset(bool stop = true) {
    elapsed_ = 0;

    if (stop) {
      state_ = State::STOPPED;
    }
  }

  bool isRunning() const {
    return state_ == State::RUNNING;
  }

  int64_t elapsedMicroseconds() const {
    return elapsed_ * 1000;
  }

  double elapsedMicrosecondsF() const {
    return elapsed_ * 1000.0;
  }

  int64_t elapsedMilliseconds() const {
    return elapsed_;
  }

  double elapsedMillisecondsF() const {
    return elapsed_;
  }

  int64_t elapsedSeconds() const {
    return elapsed_ / 1000;
  }

  double elapsedSecondsF() const {
    return elapsed_ / 1000.0;
  }

  void pause() {
    stop();
  }

  void resume() {
    start();
  }

  void tickIfRunning(int64_t microseconds) {
    if (state_ == State::RUNNING) {
      elapsed_ += microseconds;
    }
  }

  void tick(int64_t microseconds) {
    elapsed_ += microseconds;
  }

protected:
  int64_t getElapsed() const {
    int64_t elapsed = elapsed_;
    if (state_ == State::RUNNING) {
      elapsed += stop_time_ - start_;
    }
    return elapsed;
  }

private:
  int64_t start_ = 0;
  int64_t stop_time_ = 0;
  int64_t elapsed_ = 0;
  State state_ = State::STOPPED;
};

} // namespace bst

#endif // BOOST_ERSEAT_HPP_