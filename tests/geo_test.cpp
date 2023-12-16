#include <BoosterSeat/geo.hpp>

#include "gtest/gtest.h"

using namespace bst::geo;

#include <iostream>

TEST(Geo, Distance) {
  Point point_1{38.889200, -77.050114};
  Point point_2{38.889795, -77.009188};
  EXPECT_NEAR(distance(point_1, point_2), 3.5, 0.1);

  Point point_3{38.889475, -77.035253};
  Point point_4{19.472150, -155.592207};
  EXPECT_NEAR(distance(point_3, point_4), 7700.0, 10);
}
