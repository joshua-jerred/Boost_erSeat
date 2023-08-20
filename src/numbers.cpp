#include <Bst/numbers.hpp>

double BoosterSeat::doubleToPrecisionTwo(double d) {
  int i;
  if (d >= 0) {
    i = static_cast<int>(d * 100 + 0.5);
  } else {
    i = static_cast<int>(d * 100 - 0.5);
  }
  return (i / 100.0);
}