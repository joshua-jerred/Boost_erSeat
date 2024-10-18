/**
 * @file timer_test.cpp
 * @date 2024-10-17
 * @author Joshua Jerred (https://joshuajer.red)
 * @copyright Copyright (c) 2023
 */

#include "gtest/gtest.h"

#include <BoosterSeat/sleep.hpp>
#include <BoosterSeat/timer.hpp>

TEST(bst_timer, Timer_basic_test) {
  bst::Timer timer(5);

  EXPECT_FALSE(timer.isDone());
  bst::sleep(6);
  EXPECT_TRUE(timer.isDone());
  timer.reset();
  EXPECT_FALSE(timer.isDone());
  bst::sleep(4);
  EXPECT_FALSE(timer.isDone());
  bst::sleep(2);
  EXPECT_TRUE(timer.isDone());

  // Test set timeout
  timer.setTimeout(2);
  timer.reset();
  EXPECT_FALSE(timer.isDone());
  bst::sleep(1);
  EXPECT_FALSE(timer.isDone());
  bst::sleep(1);
  EXPECT_TRUE(timer.isDone());

  // Test set done
}

TEST(bst_timer, SoftwareTimer_basic_test) {
  bst::SoftwareTimer timer;

  // Initial state should be the same as a regular timer
  EXPECT_FALSE(timer.isDone());

  timer.setDone();
  EXPECT_TRUE(timer.isDone());

  timer.reset();
  EXPECT_FALSE(timer.isDone());

  timer.setDone();
  EXPECT_TRUE(timer.isDone());
  timer.setNotDone();
  EXPECT_FALSE(timer.isDone());
}