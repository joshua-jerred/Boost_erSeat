#include <iostream>

#include <BoosterSeat/rolling_average.hpp>

#include "gtest/gtest.h"

TEST(RollingAverageTest, General) {
  bst::RollingAverage avg(4);
  avg.addValue(1);
  EXPECT_EQ(avg.getAverage(), 1);
  avg.addValue(2);
  EXPECT_NEAR(avg.getAverage(), 1.5, 0.0001);
  avg.addValue(3);
  EXPECT_NEAR(avg.getAverage(), 2, 0.0001);
  avg.addValue(4);
  EXPECT_NEAR(avg.getAverage(), 2.5, 0.0001);
  avg.addValue(5);
  EXPECT_NEAR(avg.getAverage(), 3.5, 0.0001);
  avg.addValue(0);
  avg.addValue(0);
  avg.addValue(0);
  avg.addValue(0);
  EXPECT_NEAR(avg.getAverage(), 0, 0.0001);
  avg.addValue(1);
  EXPECT_NEAR(avg.getAverage(), 0.25, 0.0001);
}