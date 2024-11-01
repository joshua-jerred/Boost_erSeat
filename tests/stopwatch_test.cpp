#include <iostream>

#include <BoosterSeat/sleep.hpp>
#include <BoosterSeat/stopwatch.hpp>

#include "gtest/gtest.h"

TEST(bst_stopwatch, DefaultConstructor) {
  bst::Stopwatch stopwatch;
  EXPECT_FALSE(stopwatch.isRunning());
  EXPECT_EQ(stopwatch.elapsedMicroseconds(), 0);
}

TEST(bst_stopwatch, StartAndStop) {
  bst::Stopwatch stopwatch;
  stopwatch.start();
  EXPECT_TRUE(stopwatch.isRunning());
  stopwatch.stop();
  EXPECT_FALSE(stopwatch.isRunning());
}

TEST(bst_stopwatch, Units) {
  bst::Stopwatch stopwatch;
  stopwatch.start();
  bst::sleep(10);
  stopwatch.stop();

  EXPECT_NEAR(stopwatch.elapsedMicrosecondsF(), 10000, 500);
  EXPECT_NEAR(stopwatch.elapsedMillisecondsF(), 10, 0.5);
  EXPECT_NEAR(stopwatch.elapsedSecondsF(), 0, 0.05);
}

TEST(bst_stopwatch, KeepsRunningTotal) {
  constexpr double kEpsilon = 0.001;

  bst::Stopwatch stopwatch;
  stopwatch.start();
  bst::sleep(10);
  stopwatch.stop();
  EXPECT_NEAR(stopwatch.elapsedSecondsF(), 0.01, kEpsilon);

  bst::sleep(20);

  stopwatch.start();
  bst::sleep(10);
  stopwatch.stop();
  EXPECT_NEAR(stopwatch.elapsedSecondsF(), 0.02, kEpsilon);

  bst::sleep(20);

  stopwatch.start();
  bst::sleep(80);
  stopwatch.stop();
  EXPECT_NEAR(stopwatch.elapsedSecondsF(), 0.1, kEpsilon);
}

TEST(bst_stopwatch, ResetStopsByDefault) {
  bst::Stopwatch stopwatch;
  stopwatch.start();
  bst::sleep(5);

  // verify that calling ::reset() stops the stopwatch by default.
  EXPECT_TRUE(stopwatch.isRunning());
  EXPECT_GT(stopwatch.elapsedMicroseconds(), 0);
  stopwatch.reset();
  EXPECT_FALSE(stopwatch.isRunning());
  EXPECT_EQ(stopwatch.elapsedMicroseconds(), 0);
}

TEST(bst_stopwatch, ResetKeepsRunning) {
  bst::Stopwatch stopwatch;
  stopwatch.start();
  bst::sleep(5);

  // verify that calling ::reset(false) keeps the stopwatch running.
  EXPECT_TRUE(stopwatch.isRunning());
  EXPECT_GT(stopwatch.elapsedMicroseconds(), 0);
  stopwatch.reset(false);
  EXPECT_TRUE(stopwatch.isRunning());
}

TEST(bst_stopwatch, IStopwatch) {
  bst::Stopwatch sw;
  bst::IStopwatch &iStopWatch = sw;

  iStopWatch.start();
  bst::sleep(10);
  iStopWatch.stop();
  EXPECT_NEAR(iStopWatch.elapsedMilliseconds(), 10, 1);
}

TEST(bst_stopwatch, SoftwareStopwatch) {
  bst::SoftwareStopwatch sw;
  bst::IStopwatch &iStopWatch = sw;

  iStopWatch.start();

  sw.tick(10);

  iStopWatch.stop();
  EXPECT_NEAR(iStopWatch.elapsedMilliseconds(), 10, 1);
}