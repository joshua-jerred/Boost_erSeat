#ifndef BST_ROLLING_AVERAGE_HPP_
#define BST_ROLLING_AVERAGE_HPP_

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
  RollingAverage(int window_size);

  /**
   * @brief Default destructor
   */
  ~RollingAverage() = default;

  void addValue(double value);

  /**
   * @brief This method returns the rolling average.
   * @return double - the rolling average
   */
  double getAverage() const;

private:
  std::queue<double> queue_ = {};
  unsigned int window_size_;
  double sum_ = 0;
};

} // namespace bst

#endif /* ROLLING_AVERAGE_HPP_ */