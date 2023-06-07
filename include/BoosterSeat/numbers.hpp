#ifndef NUMBERS_HPP_
#define NUMBERS_HPP_

#include <cmath>

namespace BoosterSeat {

namespace numbers {

/**
 * @brief Rounds a double to two decimal places.
 * @example 1.2345 -> 1.23
 * @param d  The double to round.
 * @return double The rounded double.
 */
inline double doubleToPrecisionTwo(double d) {
  int i;
  if (d >= 0)
    i = static_cast<int>(d * 100 + 0.5);
  else
    i = static_cast<int>(d * 100 - 0.5);
  return (i / 100.0);
}

/**
 * @todo needs to be tested.
 * 
 * @brief Just a simple function to compare two doubles by a given epsilon.
 *
 * @param a - The first double.
 * @param b - The second double.
 * @param epsilon - The maximum difference between the two doubles.
 * @return true - The two doubles are equal.
 * @return false - The two doubles are not equal.
 */
inline bool isApproxEqual(const double a, const double b, const double epsilon) {
  return std::abs(a - b) <= epsilon;
}

/**
 * 
 * @todo needs to be tested.
 * 
 * @brief 
 * 
 * @param a 
 * @param b 
 * @param percent - value between 0.0 and 1.0
 * @return true 
 * @return false 
 */
inline bool isApproxEqualPercent(const double a, const double b,
                          const double percent) {
  return isApproxEqual(a, b, percent * std::max(a, b));
}

} // namespace numbers

} // namespace BoosterSeat

#endif /* NUMBERS_HPP_ */