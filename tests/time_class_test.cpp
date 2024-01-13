#include <BoosterSeat/sleep.hpp>
#include <BoosterSeat/time.hpp>

#include "gtest/gtest.h"

using namespace bst;

#include <iostream>

TEST(bstTimeClass, constructors) {
  // default constructor
  bst::Time time1 = bst::Time();
  EXPECT_EQ(time1.toString(), "1970-01-01 00:00:00");
  EXPECT_LT(time1.secondsFromNow(), 50 * 365 * 24 * 60 * 60 * -1); // 50 years

  // current time constructor
  bst::Time time2 = bst::Time(true);
  EXPECT_EQ(time2.secondsFromNow(), 0);
}

TEST(bstTimeClass, basic_string) {
  std::string time_string = "2020-01-01 00:00:01";
  bst::Time time;

  EXPECT_TRUE(time.fromString(time_string));
  EXPECT_EQ(time.toString(), time_string);

  // during daylight savings time
  std::string time_string_dst = "2020-06-01 00:00:01";
  bst::Time time_dst;

  EXPECT_TRUE(time_dst.fromString(time_string_dst));
  EXPECT_EQ(time_dst.toString(), time_string_dst);
}

TEST(bstTimeClass, getters) {
  std::string time_string = "2020-02-10 01:10:01";
  bst::Time time;

  ASSERT_TRUE(time.fromString(time_string));

  EXPECT_EQ(time.getYear(), 2020);
  EXPECT_EQ(time.getMonth(), 2);
  EXPECT_EQ(time.getDay(), 10);
  EXPECT_EQ(time.getHour(), 1);
  EXPECT_EQ(time.getMinute(), 10);
  EXPECT_EQ(time.getSecond(), 1);
}

TEST(bstTimeClass, setToNow) {
  bst::Time time;
  time.setToNow();

  std::time_t now = std::time(nullptr);
  std::tm tm = *std::gmtime(&now);

  EXPECT_EQ(time.getYear(), tm.tm_year + 1900);
  EXPECT_EQ(time.getMonth(), tm.tm_mon + 1);
  EXPECT_EQ(time.getDay(), tm.tm_mday);
  EXPECT_EQ(time.getHour(), tm.tm_hour);
  EXPECT_EQ(time.getMinute(), tm.tm_min);
  EXPECT_EQ(time.getSecond(), tm.tm_sec);
}

TEST(bstTimeClass, greaterThanLessThanOperators) {
  bst::Time time1;
  bst::Time time2;

  time1.fromString("2020-01-01 00:00:01");
  time2.fromString("2020-01-01 00:00:02");

  EXPECT_TRUE(time1 < time2);
  EXPECT_TRUE(time2 > time1);
  EXPECT_TRUE(time1 <= time2);
  EXPECT_TRUE(time2 >= time1);
  EXPECT_TRUE(time1 != time2);
  EXPECT_FALSE(time1 == time2);

  time1.fromString("2020-01-01 00:00:01");
  time2.fromString("2020-01-01 00:00:01");

  EXPECT_FALSE(time1 < time2);
  EXPECT_FALSE(time2 > time1);
  EXPECT_TRUE(time1 <= time2);
  EXPECT_TRUE(time2 >= time1);
  EXPECT_FALSE(time1 != time2);
  EXPECT_TRUE(time1 == time2);

  time1.fromString("2020-01-01 00:00:02");
  time2.fromString("2020-01-01 00:00:01");

  EXPECT_FALSE(time1 < time2);
  EXPECT_FALSE(time2 > time1);
  EXPECT_FALSE(time1 <= time2);
  EXPECT_FALSE(time2 >= time1);
  EXPECT_TRUE(time1 != time2);
  EXPECT_FALSE(time1 == time2);
}

TEST(bstTimeClass, secondsFromNow) {
  bst::Time time;
  int64_t seconds_delta;

  // Test that times in the past have a negative delta
  ASSERT_TRUE(time.fromString("2000-01-01 00:00:00"));
  seconds_delta = time.secondsFromNow();
  EXPECT_LT(seconds_delta, -756864000); // 23 years

  // Test that times in the future have a positive delta
  ASSERT_TRUE(time.fromString("2050-01-01 00:00:00"));
  seconds_delta = time.secondsFromNow();
  EXPECT_GT(seconds_delta, 473040000); // 20 years

  // Test that the time 'now' has a delta of 0 seconds
  time.setToNow();
  seconds_delta = time.secondsFromNow();
  EXPECT_EQ(seconds_delta, 0);

  // Block for 1 second and test that the delta is -1
  bst::sleep(1000);
  seconds_delta = time.secondsFromNow();
  EXPECT_EQ(seconds_delta, -1);
}