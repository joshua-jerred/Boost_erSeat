/**
 * @file geo.hpp
 * @author Joshua Jerred (https://joshuajer.red)
 * @brief A collection of structures for representing geographic data.
 * @date 2023-06-12
 * @copyright Copyright (c) 2023
 */

#ifndef BOOSTERSEAT_GEO_HPP_
#define BOOSTERSEAT_GEO_HPP_

#include <vector>

namespace bst {
namespace geo {

inline constexpr double EARTH_RADIUS_KM = 6378.1370;

/**
 * @brief A geographical point.
 */
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

  Point shootVector(double bearing, double distance_m) const;

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

/**
 * @brief Get the distance between two points in kilometers.
 *
 * @param point_a The first point.
 * @param point_b The second point.
 * @return double The distance between the two points in kilometers.
 */
double distance(const Point &point_a, const Point &point_b);

/**
 * @brief A path of geographical points.
 */
class Path {
public:
  Path();
  Path(std::vector<Point> points);

  void addPoint(Point point) {
    points_.push_back(point);
  }

  int getNumPoints() const {
    return points_.size();
  }

  double distance() const;

  std::vector<Point> points() const {
    return points_;
  }

  bool getLastPoint(Point &point) const;

  bool getFirstPoint(Point &point) const;

private:
  std::vector<Point> points_;
};

} // namespace geo
} // namespace bst

#endif /* GEO_HPP_ */