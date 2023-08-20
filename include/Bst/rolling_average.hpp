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

  /**
   * @brief This method increases the 'count' within the current interval.
   * @param count - The amount to increase the count by, default is 1.0
   */
  void count(double count = 1.0);

  /**
   * @brief This method should be called at the end of a set interval.
   * @details Example: If the window size is 60 minutes, this method should be
   * called at the end of each minute to get the average per minute over the
   * last 60 minutes.
   */
  void intervalCall();

  /**
   * @brief This method returns the rolling average.
   * @return double - the rolling average
   */
  double getAverage() const;

private:
  std::queue<double> queue_ = {};
  unsigned int window_size_;
  double sum_ = 0;
  double count_ = 0;
};

} // namespace BoosterSeat

#endif /* ROLLING_AVERAGE_HPP_ */