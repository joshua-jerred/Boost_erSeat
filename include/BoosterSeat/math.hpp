/**
 * @file math.hpp
 * @author Joshua Jerred (https://joshuajer.red)
 * @brief Contains general math functions/constants.
 * @date 2023-12-16
 * @copyright Copyright (c) 2023
 */

#ifndef BOOSTER_SEAT_MATH_HPP_
#define BOOSTER_SEAT_MATH_HPP_

namespace bst::math {

/// @brief The mathematical constant pi.
inline constexpr double PI = 3.14159265358979323846;

/// @brief Two times pi.
inline constexpr double TWO_PI = 2.0 * PI;

/// @brief Factor to convert degrees to radians.
inline constexpr double D2R = PI / 180.0;

} // namespace bst::math

#endif /* BOOSTER_SEAT_MATH_HPP_ */