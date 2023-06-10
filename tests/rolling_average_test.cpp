#include <iostream>

#include <BoosterSeat/rolling_average.hpp>

#include "gtest/gtest.h"

using namespace BoosterSeat;

TEST(StopwatchTest, DefaultConstructor) {
  RollingAverage avg(4);
  EXPECT_EQ(avg.getAverage(), 0.0);
  avg.count();
  EXPECT_EQ(avg.getAverage(), 0.0);
  avg.count();
  avg.intervalCall();
  EXPECT_EQ(avg.getAverage(), 2.0);
  avg.intervalCall();
  EXPECT_EQ(avg.getAverage(), 1.0);
  avg.count(10);
  avg.intervalCall();
  EXPECT_EQ(avg.getAverage(), 4.0);
  avg.count(10);
  avg.intervalCall();
  EXPECT_EQ(avg.getAverage(), 5.5);
  avg.intervalCall();
  EXPECT_EQ(avg.getAverage(), 5.0);
}