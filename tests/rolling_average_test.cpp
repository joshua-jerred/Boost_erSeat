#include <iostream>

#include <BoosterSeat/rolling_average.hpp>

#include "gtest/gtest.h"

TEST(bst_rolling_average, General) {
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

TEST(bst_rolling_average, ChangeWindowSize) {
  bst::RollingAverage avg(4);
  avg.addValue(10);
  avg.addValue(1);
  avg.addValue(2);
  avg.addValue(3);
  avg.setWindowSize(3);
  EXPECT_NEAR(avg.getAverage(), 2, 0.0001);
}

TEST(bst_rolling_average, RemoveOldest) {
  bst::RollingAverage avg(4);
  avg.addValue(10);
  avg.addValue(1);
  avg.addValue(2);
  avg.addValue(3);
  avg.removeOldest();

  EXPECT_EQ(avg.getNumElements(), 3);
  EXPECT_NEAR(avg.getAverage(), 2, 0.0001);
}