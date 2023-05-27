#include <iostream>

#include <BoosterSeat/stopwatch.hpp>
#include <BoosterSeat/sleep.hpp>

#include "gtest/gtest.h"

using namespace BoosterSeat;

void secondsEq(const double a, const double b, const double epsilon) {
  EXPECT_LE(std::abs(a - b), epsilon);
}

TEST(StopwatchTest, DefaultConstructor) {
  Stopwatch stopwatch;
  EXPECT_EQ(stopwatch.state(), Stopwatch::State::STOPPED);
  EXPECT_EQ(stopwatch.elapsed(), 0.0);
}

TEST(StopwatchTest, StartAndStop) {
  Stopwatch stopwatch;
  stopwatch.start();
  EXPECT_EQ(stopwatch.state(), Stopwatch::State::RUNNING);
  stopwatch.stop();
  EXPECT_EQ(stopwatch.state(), Stopwatch::State::STOPPED);
}

TEST(Stopwatch, Units) {
  constexpr double kEpsilon = 0.001;

  Stopwatch stopwatch;
  stopwatch.start();
  util::sleep(10);
  stopwatch.stop();
  secondsEq(stopwatch.elapsed(Resolution::SECONDS), 0.01, kEpsilon);
  secondsEq(stopwatch.elapsed(Resolution::MILLISECONDS), 10.0, kEpsilon * 1000);
  secondsEq(stopwatch.elapsed(Resolution::MICROSECONDS), 10000.0,
            kEpsilon * 1000000);
}

TEST(StopwatchTest, KeepsRunningTotal) {
  constexpr double kEpsilon = 0.001;

  Stopwatch stopwatch;
  stopwatch.start();
  util::sleep(10);
  stopwatch.stop();
  secondsEq(stopwatch.elapsed(), 0.01, kEpsilon);

  util::sleep(20);

  stopwatch.start();
  util::sleep(10);
  stopwatch.stop();
  secondsEq(stopwatch.elapsed(), 0.02, kEpsilon);

  util::sleep(20);

  stopwatch.start();
  util::sleep(980);
  stopwatch.stop();
  secondsEq(stopwatch.elapsed(), 1.0, kEpsilon);
}