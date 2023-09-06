/**
 * @file gpio.hpp
 * @author Joshua Jerred (https://joshuajer.red)
 * @brief BoosterSeatEmbedded GPIO Interface
 * @date 2023-08-07
 * @copyright Copyright (c) 2023
 */

#ifndef BST_EMBD_STOPWATCH_HPP_
#define BST_EMBD_STOPWATCH_HPP_

#include <cstdint>

namespace bst {

/**
 * @brief A simple stopwatch class for embedded targets.
 * @warning Does not provide protection against timer overflows!
 */
class Stopwatch {
public:
  Stopwatch() = default;
  ~Stopwatch() = default;

  /**
   * @brief Start/resume the stopwatch.
   * @details Resume it if it was paused. Resets the total elapsed time if it
   * was already running.
   */
  void start();

  /**
   * @brief Just like start(), but if it's already running it will not reset the
   * elapsed time, it will just continue running.
   */
  void resume();

  /**
   * @brief Pause the stopwatch.
   * @details Does nothing if the stopwatch is already paused. Keeps track of
   * total elapsed time.
   */
  void pause();

  /**
   * @brief Reset the stopwatch to 0. If running, it will continue running, but
   * will reset the time.
   */
  void reset();

  /**
   * @brief Get the Elapsed Ticks
   *
   * @return uint32_t - The number of ticks elapsed since the stopwatch was
   * started.
   */
  uint32_t getElapsedTicks();

  bool isRunning() const {
    return is_running_;
  }

private:
  uint32_t start_tick_ = 0;
  uint32_t total_elapsed_ticks_ = 0;
  bool is_running_ = false;
};

} // namespace bst

#endif /* BSTE_GPIO_HPP_ */