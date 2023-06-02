#ifndef NUMBERS_HPP_
#define NUMBERS_HPP_

namespace BoosterSeat {

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

}  // namespace BoosterSeat

#endif /* NUMBERS_HPP_ */