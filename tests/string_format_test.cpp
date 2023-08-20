// just a simple visual test

#include <Bst/string_formatting.hpp>
#include <string>
#include <vector>

#include "gtest/gtest.h"

TEST(string_format, intToHex) {
  EXPECT_EQ(BoosterSeat::string::intToHex(1), "0x01");
  EXPECT_EQ(BoosterSeat::string::intToHex(255), "0xFF");
  EXPECT_EQ(BoosterSeat::string::intToHex(255, 1), "0xFF");
  EXPECT_EQ(BoosterSeat::string::intToHex(255, 4), "0x00FF");
  EXPECT_EQ(BoosterSeat::string::intToHex(255, 4, false), "00FF");
  EXPECT_EQ(BoosterSeat::string::intToHex(255, 4, false, false), "00ff");
}
