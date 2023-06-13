/**
 * @file geo.hpp
 * @author Joshua Jerred (https://joshuajer.red)
 * @brief A collection of structures for representing geographic data.
 * @date 2023-06-12
 * @copyright Copyright (c) 2023
 */

#ifndef BOOSTERSEAT_GEO_HPP_
#define BOOSTERSEAT_GEO_HPP_

namespace BoosterSeat {
namespace geo {

class Point {
public:
  Point(double lat, double lon);
  double lat() const;
  double lon() const;

private:
  double lat_;
  double lon_;
};

} // namespace geo
} // namespace BoosterSeat

#endif /* GEO_HPP_ */