/**
 * @file filters.hpp
 * @author Joshua Jerred (https://joshuajer.red)
 * @brief
 * @date 2024-09-07
 * @copyright Copyright (c) 2024
 */

#pragma once

#include <cstddef>

namespace bst {

/// @brief A simple counting filter that allows for some noise.
/// @tparam T The type of data to filter (enumerations generally).
template <class T>
class ConsecutiveValuesFilter {
public:
  /// @brief Constructor for the ConsecutiveValuesFilter.
  /// @param initial_value The initial value to set the filter to.
  /// @param filter_threshold The number of consecutive values that must be seen
  /// before the filter will pass the value.
  ConsecutiveValuesFilter(T initial_value, size_t filter_threshold = 0)
      : filter_threshold_{filter_threshold}, current_value_{initial_value},
        new_value_{initial_value} {
  }

  /// @brief Destructor for the ConsecutiveValuesFilter.
  ~ConsecutiveValuesFilter() = default;

  /// @brief Resets the filter's counter and sets the current value.
  /// @param value The value to set the current value to.
  void reset(T value) {
    current_count_ = 0;
    current_value_ = value;
  }

  void setFilterThreshold(size_t filter_threshold) {
    filter_threshold_ = filter_threshold;
  }

  /// @brief The input stream for this filter.
  /// @param value The input
  /// @return \c true if the filtered value has changed, \c false otherwise.
  bool addValue(T value) {
    // If the value is the same as the current value, decrement the count until
    // it's back to zero.
    if (value == current_value_) {
      if (current_count_ != 0) {
        current_count_--;
      }
      return false;
    }

    // If the value is the same as the currently being counted value, increment
    // the count.
    if (value == new_value_) {
      current_count_++;
    } else {
      // If the value is different from the current or the new value, reset the
      // count and set the new, new value.
      new_value_ = value;
      current_count_ = 1;
    }

    // If the count is greater than the filter threshold, set the current value
    // to the new value and reset the count.
    if (current_count_ >= filter_threshold_) {
      current_value_ = new_value_;
      current_count_ = 0;
      return true;
    }

    return false;
  }

  /// @brief Returns the current value.
  T getCurrentValue() const {
    return current_value_;
  }

private:
  /// @brief The filter threshold.
  size_t filter_threshold_;

  /// @brief The current count of consecutive new values.
  size_t current_count_{0};

  /// @brief The current value.
  T current_value_{};

  /// @brief The new value that is being counted.
  T new_value_{};
};

} // namespace bst