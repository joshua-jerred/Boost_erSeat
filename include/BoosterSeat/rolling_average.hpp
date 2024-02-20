#ifndef BST_ROLLING_AVERAGE_HPP_
#define BST_ROLLING_AVERAGE_HPP_

#include <cstddef>
#include <queue>

namespace bst {

/**
 * @brief Moving average calculator
 * @details This class calculates the moving average over a rolling window.
 */
class RollingAverage {
public:
  /**
   * @brief Construct a RollingAverage object
   * @param window_size - The size of the rolling window
   */
  RollingAverage(size_t window_size);

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
  void addValue(double value);

  /**
   * @brief This method returns the rolling average.
   * @return double - the rolling average
   */
  double getAverage() const;

  /**
   * @brief Set the window size. If the new window size is smaller than the
   * current queue size, the queue will be truncated.
   * @param new_window_size - The new window size
   */
  void setWindowSize(size_t new_window_size);

private:
  std::queue<double> queue_ = {};
  size_t window_size_;
  double sum_ = 0;
};

} // namespace bst

#endif /* ROLLING_AVERAGE_HPP_ */