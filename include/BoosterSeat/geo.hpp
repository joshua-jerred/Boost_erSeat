/**
 * @file geo.hpp
 * @author Joshua Jerred (https://joshuajer.red)
 * @brief A collection of structures for representing geographic data.
 * @date 2023-06-12
 * @copyright Copyright (c) 2023
 */

#ifndef BOOSTERSEAT_GEO_HPP_
#define BOOSTERSEAT_GEO_HPP_

namespace bst {
namespace geo {

class Point {
public:
  Point();

  /**
   * @brief Construct a new geographical point at the given latitude and
   * longitude.
   * @param latitude The latitude in degrees decimal.
   * @param longitude The longitude in degrees decimal.
   */
  Point(double latitude, double longitude);

  double latitude() const {
    return lat_;
  }
  double longitude() const {
    return lon_;
  }

private:
  /**
   * @brief Latitude in degrees decimal. North is positive, south is negative.
   */
  double lat_;

  /**
   * @brief Longitude in degrees decimal. East is positive, west is negative.
   */
  double lon_;
};

double distance(const Point &a, const Point &b);

} // namespace geo
} // namespace bst

#endif /* GEO_HPP_ */