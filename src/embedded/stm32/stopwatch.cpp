/**
 * @file stopwatch.cpp
 * @author Joshua Jerred (https://joshuajer.red)
 * @brief STM32 Stopwatch Implementation
 * @date 2023-08-28
 * @copyright Copyright (c) 2023
 */

#include <Bst/Embd/embd.hpp>

#include <Bst/Embd/stopwatch.hpp>

#include STM32_HAL_INCLUDE

namespace bst {
void Stopwatch::start() {
  is_running_ = true;
  start_tick_ = HAL_GetTick();
  total_elapsed_ticks_ = 0;
}

void Stopwatch::resume() {
  if (!is_running_) {
    start();
  }
}

void Stopwatch::pause() {
  if (!is_running_) {
    return;
  }

  is_running_ = false;
  total_elapsed_ticks_ += HAL_GetTick() - start_tick_;
}

void Stopwatch::reset() {
  total_elapsed_ticks_ = 0;
  start_tick_ = HAL_GetTick();
}

uint32_t Stopwatch::getElapsedTicks() {
  if (is_running_) {
    return total_elapsed_ticks_ + (HAL_GetTick() - start_tick_);
  } else {
    return total_elapsed_ticks_;
  }
}
} // namespace bst