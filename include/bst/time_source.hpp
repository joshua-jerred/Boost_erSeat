/// @file time_source.hpp
/// @author Joshua Jerred (https://joshuajer.red)
/// @brief A time source for the BoosterSeat library.
/// @date 2025-02-15
/// @copyright Copyright (c) 2025

#pragma once

#include <chrono>
#include <cstdint>

#include <BoosterSeat/clock.hpp>

namespace bst {

/// @brief An interface for a generic time/clock/tick source.
/// @details The purpose of this class is to provide a generic interface for
/// access to regular types (uint) when time is needed.
class ITimeSource {
public:
  virtual ~ITimeSource() = default;

  /// @brief A time source that is required to increment by 1 every nanosecond.
  /// @details This value has an arbitrary starting point and is not required to
  /// be the system time. It is only required to increment by 1 every
  /// nanosecond. This also means that there is risk of overflow, individual
  /// implementations can define how they handle this.
  /// @warning Overflow risk and arbitrary starting point, see details.
  /// @return uint32_t - The current time in microseconds.
  virtual uint64_t getTicksNs() const = 0;

  /// @brief Get the current time in microseconds.
  /// @warning Overflow risk and arbitrary starting point, see details of
  /// getTicksNs().
  /// @return uint64_t - The current time in microseconds.
  // virtual uint64_t getTicksUs() const = 0;

  /// @brief Get the current time in milliseconds.
  /// @warning Overflow risk and arbitrary starting point, see details of
  /// getTicksNs().
  /// @return uint64_t - The current time in milliseconds.
  // virtual uint64_t getTicksMs() const = 0;
};

/// @brief A time source that uses the <chrono> library to get the system time.
class HighResolutionTimeSource : public ITimeSource {
public:
  uint64_t getTicksNs() const override {
    return std::chrono::duration_cast<std::chrono::nanoseconds>(
               std::chrono::high_resolution_clock::now().time_since_epoch())
        .count();
  }

  // uint64_t getTicksUs() const override {
  //   return std::chrono::duration_cast<std::chrono::microseconds>(
  //              std::chrono::system_clock::now().time_since_epoch())
  //       .count();
  // }

  // uint64_t getTicksMs() const override {
  //   return std::chrono::duration_cast<std::chrono::milliseconds>(
  //              std::chrono::system_clock::now().time_since_epoch())
  //       .count();
  // }
};

} // namespace bst