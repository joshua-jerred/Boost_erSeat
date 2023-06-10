#ifndef ROLLING_AVERAGE_HPP_
#define ROLLING_AVERAGE_HPP_

#include <queue>

namespace BoosterSeat {

/**
 * @brief This class declares a rolling average.
 * @details This class is used to calculate a rolling average over a set
 * interval. The two things that can be changed are the window size and the
 * rate at which the user calls the intervalCall() method.
 *
 * @example
 * Window size = 60 minutes
 * intervalCall() is called every minute
 * This will give you the average per minute over the last 60 minutes.
 *
 * @tparam T - The type of the rolling average ex:
 * (int for count, double for rate)
 */
template <class T>
class RollingAverage {
public:
  /**
   * @brief Construct a RollingAverage object
   * @param window_size - The size of the rolling window
   */
  RollingAverage(int window_size) : window_size_(window_size) {
  }

  /**
   * @brief Default destructor
   */
  ~RollingAverage() = default;

  /**
   * @brief This method should be called at the end of a set interval.
   * @details Example: If the window size is 60 minutes, this method should be
   * called at the end of each minute to get the average per minute over the
   * last 60 minutes.
   */
  void intervalCall() {
    queue_.push(count_);
    sum_ += count_;
    count_ = 0.0;

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
  double getAverage() const {
    unsigned int size = queue_.size();
    if (size == 0) {
      return 0.0;
    }
    return sum_ / static_cast<T>(queue_.size());
  }

  /**
   * @brief This method increases the 'count' within the current interval.
   * @param count - The amount to increase the count by, default is 1.0
   */
  void count(T count = 1.0) {
    count_ += count;
  }

private:
  std::queue<T> queue_ = {};
  unsigned int window_size_;
  T sum_ = 0;
  T count_ = 0;
};

} // namespace BoosterSeat

#endif /* ROLLING_AVERAGE_HPP_ */