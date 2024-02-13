#ifndef NUMBERS_HPP_
#define NUMBERS_HPP_

#include <cmath>
#include <iomanip>
#include <sstream>

namespace bst {

/**
 * @brief Rounds a double to two decimal places. For example: 1.2345 -> 1.23
 * @param double  The double to round.
 * @return double The rounded double.
 */
double doubleToPrecisionTwo(double);

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
inline bool isApproxEqual(double a, double b, double epsilon) {
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

inline std::string rndTs(double d, int precision) {
  std::stringstream ss;
  ss << std::fixed << std::setprecision(precision) << d;
  return ss.str();
}

} // namespace bst

#endif /* NUMBERS_HPP_ */