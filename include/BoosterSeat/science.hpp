/**
 * @file science.hpp
 * @author Joshua Jerred (https://joshuajer.red)
 * @brief BoosterSeat science module
 * @date 2024-02-13
 * @copyright Copyright (c) 2024
 */

#ifndef BST_SCIENCE_HPP_
#define BST_SCIENCE_HPP_

namespace bst {

/// @brief Standard gravity constant
inline constexpr double K_GRAVITY = 9.80665;

class Pressure {
public:
  Pressure() = default;

  void setFromPascals(double pascals);
  double pascals() const;

  void setFromMillibars(double millibars);
  double millibars() const;

  void setFromInchesMercury(double inches_mercury);
  double inchesMercury() const;

  void setFromPSI(double psi);
  double psi() const;

  void setFromAtmospheres(double atmospheres);
  double atmospheres() const;

private:
  double pressure_pascals_ = 0.0;
};

} // namespace bst

#endif /* BST_SCIENCE_HPP_ */