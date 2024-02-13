#include <BoosterSeat/random.hpp>

#include "gtest/gtest.h"

TEST(RandomTest, randomHexString) {
  constexpr uint32_t K_NUM_TESTS = 1000;
  for (uint32_t i = 0; i < K_NUM_TESTS; i++) {
    std::string str = bst::randomHexString(16);
    ASSERT_EQ(str.size(), 16);
    for (auto chr : str) {
      ASSERT_TRUE(isxdigit(chr));
    }
  }
}

TEST(RandomTest, randomDouble) {
  constexpr uint32_t K_NUM_TESTS = 1000;
  for (uint32_t i = 0; i < K_NUM_TESTS; i++) {
    double val = bst::randomDouble(0, 1);
    ASSERT_GE(val, 0);
    ASSERT_LE(val, 1);
  }

  for (uint32_t i = 0; i < K_NUM_TESTS; i++) {
    double val = bst::randomDouble(0, 100);
    ASSERT_GE(val, 0);
    ASSERT_LE(val, 100);
  }

  for (uint32_t i = 0; i < K_NUM_TESTS; i++) {
    double val = bst::randomDouble(-100, 100);
    ASSERT_GE(val, -100);
    ASSERT_LE(val, 100);
  }

  for (uint32_t i = 0; i < K_NUM_TESTS; i++) {
    double val = bst::randomDouble(-100, -50);
    ASSERT_GE(val, -100);
    ASSERT_LE(val, -50);
  }
}