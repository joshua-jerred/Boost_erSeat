// just a simple visual test

#include <BoosterSeat/string_formatting.hpp>
#include <string>
#include <vector>

#include "gtest/gtest.h"

TEST(string_format, intToHex) {
  EXPECT_EQ(bst::string::intToHex(1), "0x01");
  EXPECT_EQ(bst::string::intToHex(255), "0xFF");
  EXPECT_EQ(bst::string::intToHex(255, 1), "0xFF");
  EXPECT_EQ(bst::string::intToHex(255, 4), "0x00FF");
  EXPECT_EQ(bst::string::intToHex(255, 4, false), "00FF");
  EXPECT_EQ(bst::string::intToHex(255, 4, false, false), "00ff");
}
