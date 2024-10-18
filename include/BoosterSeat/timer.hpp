#ifndef TIMER_HPP_
#define TIMER_HPP_

#include <BoosterSeat/clock.hpp>
#include <BoosterSeat/exception.hpp>

namespace bst {

/// @brief Interface for a timer class
class ITimer {
public:
  /// @brief Destructor
  virtual ~ITimer() = default;

  /// @brief Reset the timer to the current time
  virtual void reset() = 0;

  /// @brief Check if the timer has expired
  virtual bool isDone() const = 0;

  /// @brief Set the timeout of the timer. Does not reset the timer.
  /// @todo Change to size_t
  virtual void setTimeout(int timeout_ms) = 0;

  /// @brief Set the timer to be done. Changes the start time.
  virtual void setDone() = 0;
};

/// @brief A simple timer class for timing events
class Timer : public ITimer {
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
  void reset() override;

  /**
   * @brief Check if the timer has expired
   * @return true if the timer has expired, false otherwise
   */
  bool isDone() const override;

  /**
   * @brief Set the timeout of the timer
   * @param timeout_ms The timeout in milliseconds
   */
  void setTimeout(int timeout_ms) override;

  /**
   * @brief Set the timer to be done. Changes the start time.
   */
  void setDone() override;

private:
  bst::clck::TimePoint start_ = bst::clck::Clock::now();
  int timeout_ms_;
};

/// @brief A software timer class for manual control
class SoftwareTimer : public ITimer {
public:
  /// @brief Default constructor
  SoftwareTimer() = default;

  /// @brief Reset the timer - Sets the timer to not done
  void reset() override {
    is_done_ = false;
  };

  /// @brief Check if the timer is done
  bool isDone() const override {
    return is_done_;
  };

  /// @brief Stubbed out - Does nothing
  void setTimeout(int timeout_ms) override {
    (void)timeout_ms;
  };

  /// @brief Set the timer to done
  void setDone() override {
    is_done_ = true;
  };

  /// @brief Set the timer to not done
  void setNotDone() {
    is_done_ = false;
  };

private:
  /// @brief The done state of the timer
  bool is_done_ = false;
};

} // namespace bst

#endif /* TIMER_HPP_ */