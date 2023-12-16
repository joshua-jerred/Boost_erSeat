#ifndef TIMER_HPP_
#define TIMER_HPP_

#include <BoosterSeat/clock.hpp>
#include <BoosterSeat/exception.hpp>

namespace bst {

/// @brief A simple timer class for timing events
class Timer {
public:
  /**
   * @brief Create a new timer with a timeout
   * @param timeout_ms The timeout in milliseconds
   */
  Timer(int timeout_ms);

  /**
   * @brief Create a new timer with a timeout of 0. Must call setTimeout before
   *       using.
   */
  Timer();

  /**
   * @brief Reset the timer to the current time
   */
  void reset();

  /**
   * @brief Check if the timer has expired
   * @return true if the timer has expired, false otherwise
   */
  bool isDone() const;

  /**
   * @brief Set the timeout of the timer
   * @param timeout_ms The timeout in milliseconds
   */
  void setTimeout(int timeout_ms);

  /**
   * @brief Set the timer to be done. Changes the start time.
   */
  void setDone();

private:
  BoosterSeat::clck::TimePoint start_ = BoosterSeat::clck::Clock::now();
  int timeout_ms_;
};
} // namespace bst

#endif /* TIMER_HPP_ */