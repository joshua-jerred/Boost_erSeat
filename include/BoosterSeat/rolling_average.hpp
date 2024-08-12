#ifndef BST_ROLLING_AVERAGE_HPP_
#define BST_ROLLING_AVERAGE_HPP_

#include <cstddef>
#include <queue>

namespace bst {

/**
 * @brief Moving average calculator
 * @details This class calculates the moving average over a rolling window.
 */
template <typename T = double>
class RollingAverage {
public:
  /**
   * @brief Construct a RollingAverage object
   * @param window_size - The size of the rolling window
   */
  RollingAverage(size_t window_size) : window_size_(window_size) {
  }

  /**
   * @brief Default destructor
   */
  ~RollingAverage() = default;

  /**
   * @brief Add a value to the rolling average. If the queue size exceeds the
   * window size, the oldest value will be removed from the queue and the sum
   * will be decremented by that value.
   * @param value - The value to add to the rolling average
   */
  void addValue(T value) {
    queue_.push(value);
    sum_ += value;

    if (queue_.size() > window_size_) {
      sum_ -=
          queue_.front(); // remove the oldest transaction count from the sum
      queue_.pop();       // and the queue
    }
  }

  /**
   * @brief This method returns the rolling average.
   * @return T - the rolling average
   */
  T getAverage() const {
    if (queue_.empty()) {
      return 0;
    }

    return static_cast<T>(sum_ / queue_.size());
  }

  /**
   * @brief Set the window size. If the new window size is smaller than the
   * current queue size, the queue will be truncated.
   * @param new_window_size - The new window size
   */
  void setWindowSize(size_t new_window_size) {
    window_size_ = new_window_size;
    while (queue_.size() > window_size_) {
      sum_ -= queue_.front();
      queue_.pop();
    }
  }

  /**
   * @brief Remove all elements from the queue and reset the sum to zero.
   */
  void clear() {
    queue_ = {};
    sum_ = 0;
  }

  /**
   * @brief Get the number of elements in the queue. This number may be less
   * than the window size.
   * @return size_t - The number of elements in the queue
   */
  size_t getNumElements() const {
    return queue_.size();
  }

  /**
   * @brief Get the window size.
   * @return size_t - The window size
   */
  size_t getWindowSize() const {
    return window_size_;
  }

  /**
   * @brief Remove the oldest element from the queue and update the sum.
   * Safe to call if the queue is empty.
   */
  void removeOldest() {
    if (!queue_.empty()) {
      sum_ -= queue_.front();
      queue_.pop();
    }
  }

private:
  std::queue<T> queue_ = {};
  size_t window_size_;
  T sum_ = 0;
};

} // namespace bst

#endif /* ROLLING_AVERAGE_HPP_ */