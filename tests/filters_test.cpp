/**
 * @file filters_test.cpp
 * @author Joshua Jerred (https://joshuajer.red)
 * @date 2024-09-07
 * @copyright Copyright (c) 2024
 */

#include <BoosterSeat/filters.hpp>

#include "gtest/gtest.h"

enum class TestEnum : uint8_t { A, B, C };

TEST(ConsecutiveValuesFilterTest, basic_filtering) {
  size_t filter_threshold = 10;
  bst::ConsecutiveValuesFilter<TestEnum> filter{TestEnum::A, filter_threshold};

  // Update to just before the filter threshold.
  for (size_t i = 0; i < filter_threshold - 1; i++) {
    filter.addValue(TestEnum::B);
  }
  EXPECT_EQ(filter.getCurrentValue(), TestEnum::A);

  // Go one over
  filter.addValue(TestEnum::B);
  EXPECT_EQ(filter.getCurrentValue(), TestEnum::B);
}

TEST(ConsecutiveValuesFilterTest, advanced_filtering) {
  size_t filter_threshold = 10;
  bst::ConsecutiveValuesFilter<TestEnum> filter{TestEnum::A, filter_threshold};

  // Update to just before the filter threshold.
  for (size_t i = 0; i < filter_threshold - 1; i++) {
    filter.addValue(TestEnum::B);
  }
  EXPECT_EQ(filter.getCurrentValue(), TestEnum::A);

  // Go backwards so we should not need two more updates to change the value.
  filter.addValue(TestEnum::A);
  EXPECT_EQ(filter.getCurrentValue(), TestEnum::A);

  // Go forward
  filter.addValue(TestEnum::B);
  EXPECT_EQ(filter.getCurrentValue(), TestEnum::A);

  // Last update
  filter.addValue(TestEnum::B);
  EXPECT_EQ(filter.getCurrentValue(), TestEnum::B);
}
