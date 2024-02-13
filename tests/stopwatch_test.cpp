#include <iostream>

#include <BoosterSeat/sleep.hpp>
#include <BoosterSeat/stopwatch.hpp>

#include "gtest/gtest.h"

void secondsEq(const double a, const double b, const double epsilon) {
  EXPECT_LE(std::abs(a - b), epsilon);
}

TEST(StopwatchTest, DefaultConstructor) {
  bst::Stopwatch stopwatch;
  EXPECT_EQ(stopwatch.state(), bst::Stopwatch::State::STOPPED);
  EXPECT_EQ(stopwatch.elapsed(), 0.0);
}

TEST(StopwatchTest, StartAndStop) {
  bst::Stopwatch stopwatch;
  stopwatch.start();
  EXPECT_EQ(stopwatch.state(), bst::Stopwatch::State::RUNNING);
  stopwatch.stop();
  EXPECT_EQ(stopwatch.state(), bst::Stopwatch::State::STOPPED);
}

TEST(Stopwatch, Units) {
  constexpr double kEpsilon = 0.001;

  bst::Stopwatch stopwatch;
  stopwatch.start();
  bst::sleep(10);
  stopwatch.stop();
  secondsEq(stopwatch.elapsed(bst::Resolution::SECONDS), 0.01, kEpsilon);
  secondsEq(stopwatch.elapsed(bst::Resolution::MILLISECONDS), 10.0,
            kEpsilon * 1000);
  secondsEq(stopwatch.elapsed(bst::Resolution::MICROSECONDS), 10000.0,
            kEpsilon * 1000000);
}

TEST(StopwatchTest, KeepsRunningTotal) {
  constexpr double kEpsilon = 0.001;

  bst::Stopwatch stopwatch;
  stopwatch.start();
  bst::sleep(10);
  stopwatch.stop();
  secondsEq(stopwatch.elapsed(), 0.01, kEpsilon);

  bst::sleep(20);

  stopwatch.start();
  bst::sleep(10);
  stopwatch.stop();
  secondsEq(stopwatch.elapsed(), 0.02, kEpsilon);

  bst::sleep(20);

  stopwatch.start();
  bst::sleep(980);
  stopwatch.stop();
  secondsEq(stopwatch.elapsed(), 1.0, kEpsilon);
}