/**
 * @file science.cpp
 * @author Joshua Jerred (https://joshuajer.red)
 * @brief The implementation of the science module
 * @date 2024-02-13
 * @copyright Copyright (c) 2024
 */

#include "BoosterSeat/science.hpp"

namespace bst {
void Pressure::setFromPascals(double pascals) {
  pressure_pascals_ = pascals;
}

double Pressure::pascals() const {
  return pressure_pascals_;
}

void Pressure::setFromMillibars(double millibars) {
  constexpr double K_PASCALS_PER_MILLIBAR = 100.0;
  pressure_pascals_ = millibars * K_PASCALS_PER_MILLIBAR;
}

double Pressure::millibars() const {
  constexpr double K_MILLIBARS_PER_PASCAL = 0.01;
  return pressure_pascals_ * K_MILLIBARS_PER_PASCAL;
}

void Pressure::setFromInchesMercury(double inches_mercury) {
  constexpr double K_PASCALS_PER_INCH_MERCURY = 3386.39;
  pressure_pascals_ = inches_mercury * K_PASCALS_PER_INCH_MERCURY;
}

double Pressure::inchesMercury() const {
  constexpr double K_INCHES_MERCURY_PER_PASCAL = 0.0002953;
  return pressure_pascals_ * K_INCHES_MERCURY_PER_PASCAL;
}

void Pressure::setFromPSI(double psi) {
  constexpr double K_PASCALS_PER_PSI = 6894.76;
  pressure_pascals_ = psi * K_PASCALS_PER_PSI;
}

double Pressure::psi() const {
  constexpr double K_PSI_PER_PASCAL = 0.00014503773773020922;
  return pressure_pascals_ * K_PSI_PER_PASCAL;
}

void Pressure::setFromAtmospheres(double atmospheres) {
  constexpr double K_PASCALS_PER_ATMOSPHERE = 101325.0;
  pressure_pascals_ = atmospheres * K_PASCALS_PER_ATMOSPHERE;
}

double Pressure::atmospheres() const {
  constexpr double K_ATMOSPHERES_PER_PASCAL = 9.869232667160128e-6;
  return pressure_pascals_ * K_ATMOSPHERES_PER_PASCAL;
}

} // namespace bst