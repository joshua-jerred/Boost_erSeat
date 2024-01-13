#include <BoosterSeat/time.hpp>

#include "gtest/gtest.h"

using namespace bst;

#include <iostream>

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