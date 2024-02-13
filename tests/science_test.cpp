#include <BoosterSeat/science.hpp>

#include "gtest/gtest.h"

TEST(Science, pressure) {
  constexpr double K_PASCALS = 100000;
  constexpr double K_MILLIBARS = 1000;
  constexpr double K_INCHES_MERCURY = 29.529983;
  constexpr double K_PSI = 14.503774;
  constexpr double K_ATMOSPHERES = 0.98692327;

  constexpr double K_DOUBLE_TOLERANCE = 0.0005;
  constexpr double K_DOUBLE_TOLERANCE_PASCALS = 0.05;

  bst::Pressure p;

  // Set from pascals
  p.setFromPascals(K_PASCALS);
  EXPECT_NEAR(p.pascals(), K_PASCALS, K_DOUBLE_TOLERANCE_PASCALS);
  EXPECT_NEAR(p.millibars(), K_MILLIBARS, K_DOUBLE_TOLERANCE);
  EXPECT_NEAR(p.inchesMercury(), K_INCHES_MERCURY, K_DOUBLE_TOLERANCE);
  EXPECT_NEAR(p.psi(), K_PSI, K_DOUBLE_TOLERANCE);
  EXPECT_NEAR(p.atmospheres(), K_ATMOSPHERES, K_DOUBLE_TOLERANCE);

  // sanity check
  p.setFromPascals(0);
  ASSERT_NEAR(p.pascals(), 0, K_DOUBLE_TOLERANCE_PASCALS);
  ASSERT_NEAR(p.millibars(), 0, K_DOUBLE_TOLERANCE);

  // Set from millibars
  p.setFromMillibars(K_MILLIBARS);
  EXPECT_NEAR(p.pascals(), K_PASCALS, K_DOUBLE_TOLERANCE_PASCALS);
  EXPECT_NEAR(p.millibars(), K_MILLIBARS, K_DOUBLE_TOLERANCE);
  EXPECT_NEAR(p.inchesMercury(), K_INCHES_MERCURY, K_DOUBLE_TOLERANCE);
  EXPECT_NEAR(p.psi(), K_PSI, K_DOUBLE_TOLERANCE);
  EXPECT_NEAR(p.atmospheres(), K_ATMOSPHERES, K_DOUBLE_TOLERANCE);

  // Set from inches mercury
  p.setFromInchesMercury(K_INCHES_MERCURY);
  EXPECT_NEAR(p.pascals(), K_PASCALS, K_DOUBLE_TOLERANCE_PASCALS);
  EXPECT_NEAR(p.millibars(), K_MILLIBARS, K_DOUBLE_TOLERANCE);
  EXPECT_NEAR(p.inchesMercury(), K_INCHES_MERCURY, K_DOUBLE_TOLERANCE);
  EXPECT_NEAR(p.psi(), K_PSI, K_DOUBLE_TOLERANCE);
  EXPECT_NEAR(p.atmospheres(), K_ATMOSPHERES, K_DOUBLE_TOLERANCE);

  // Set from psi
  p.setFromPSI(K_PSI);
  EXPECT_NEAR(p.pascals(), K_PASCALS, K_DOUBLE_TOLERANCE_PASCALS);
  EXPECT_NEAR(p.millibars(), K_MILLIBARS, K_DOUBLE_TOLERANCE);
  EXPECT_NEAR(p.inchesMercury(), K_INCHES_MERCURY, K_DOUBLE_TOLERANCE);
  EXPECT_NEAR(p.psi(), K_PSI, K_DOUBLE_TOLERANCE);
  EXPECT_NEAR(p.atmospheres(), K_ATMOSPHERES, K_DOUBLE_TOLERANCE);

  // Set from atmospheres
  EXPECT_NEAR(p.pascals(), K_PASCALS, K_DOUBLE_TOLERANCE_PASCALS);
  EXPECT_NEAR(p.millibars(), K_MILLIBARS, K_DOUBLE_TOLERANCE);
  EXPECT_NEAR(p.inchesMercury(), K_INCHES_MERCURY, K_DOUBLE_TOLERANCE);
  EXPECT_NEAR(p.psi(), K_PSI, K_DOUBLE_TOLERANCE);
  EXPECT_NEAR(p.atmospheres(), K_ATMOSPHERES, K_DOUBLE_TOLERANCE);
}
