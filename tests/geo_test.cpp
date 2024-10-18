#include <BoosterSeat/geo.hpp>

#include "gtest/gtest.h"

using namespace bst::geo;

#include <iostream>

TEST(bst_geo, Distance) {
  Point point_1{38.889200, -77.050114};
  Point point_2{38.889795, -77.009188};
  EXPECT_NEAR(distance(point_1, point_2), 3.5, 0.1);

  Point point_3{38.889475, -77.035253};
  Point point_4{19.472150, -155.592207};
  EXPECT_NEAR(distance(point_3, point_4), 7700.0, 10);
}

TEST(bst_geo, PathDistance) {
  std::vector<Point> points = {{-35.6240233453558, -160.6826134328059},
                               {-32.14417025725855, -156.9190554594102},
                               {-26.74568499863755, -157.3440121164353},
                               {-17.70743989126965, -151.5654080823589},
                               {-14.83054253114009, -137.9579193031041}};

  Path path{points};

  EXPECT_NEAR(path.distance(), 3772, 2);

  Point ret_point;
  EXPECT_TRUE(path.getLastPoint(ret_point));
  EXPECT_NEAR(ret_point.latitude(), points.back().latitude(), 0.0001);
  EXPECT_NEAR(ret_point.longitude(), points.back().longitude(), 0.0001);

  EXPECT_TRUE(path.getFirstPoint(ret_point));
  EXPECT_NEAR(ret_point.latitude(), points.front().latitude(), 0.0001);
  EXPECT_NEAR(ret_point.longitude(), points.front().longitude(), 0.0001);
}

TEST(bst_geo, ShootVector) {
  // nearby points
  Point point_1{38.889200, -77.050114};
  Point expected_point{38.889475, -77.035253};

  const double BEARING_1 = 88.63;
  const double DISTANCE_1 = 1.28964;

  Point point_2 = point_1.shootVector(BEARING_1, DISTANCE_1);

  EXPECT_NEAR(distance(point_1, point_2), DISTANCE_1, 0.1);
  EXPECT_NEAR(point_2.latitude(), expected_point.latitude(), 0.0001);
  EXPECT_NEAR(point_2.longitude(), expected_point.longitude(), 0.0001);

  // far away points
  const Point point3{38.889475, -77.035253};
  const Point expected_point2{40.689253, -74.044492};
  const double BEARING_2 = 50.98;
  const double DISTANCE_2 = 324.82824;

  Point point4 = point3.shootVector(BEARING_2, DISTANCE_2);

  EXPECT_NEAR(distance(point3, point4), DISTANCE_2, 0.6);
  EXPECT_NEAR(point4.latitude(), expected_point2.latitude(), 0.001);
}