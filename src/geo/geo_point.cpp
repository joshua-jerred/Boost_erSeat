#include <cmath>

#include <BoosterSeat/exception.hpp>
#include <BoosterSeat/geo.hpp>
#include <BoosterSeat/math.hpp>
namespace bst::geo {

Point::Point() : lat_(0.0), lon_(0.0) {
}

Point::Point(double lat, double lon) : lat_(lat), lon_(lon) {
  if (lat < -90.0 || lat > 90.0) {
    throw bst::BoosterSeatException("Latitude must be between -90.0 and 90.0",
                                    bst::ErrorNumber::GEO_INVALID_LATITUDE);
  }
  if (lon < -180.0 || lon > 180.0) {
    throw bst::BoosterSeatException(
        "Longitude must be between -180.0 and 180.0",
        bst::ErrorNumber::GEO_INVALID_LONGITUDE);
  }
}

Point Point::shootVector(double bearing, double distance_km) const {
  double in_lat_rad = lat_ * bst::math::D2R;
  double in_lon_rad = lon_ * bst::math::D2R;
  double bearing_rad = bearing * bst::math::D2R;

  double out_lat_rad =
      std::asin(std::sin(in_lat_rad) * std::cos(distance_km / EARTH_RADIUS_KM) +
                std::cos(in_lat_rad) * std::sin(distance_km / EARTH_RADIUS_KM) *
                    std::cos(bearing_rad));
  double out_lon_rad =
      in_lon_rad + std::atan2(std::sin(bearing_rad) *
                                  std::sin(distance_km / EARTH_RADIUS_KM) *
                                  std::cos(in_lat_rad),
                              std::cos(distance_km / EARTH_RADIUS_KM) -
                                  std::sin(in_lat_rad) * std::sin(out_lat_rad));

  return Point(out_lat_rad * bst::math::R2D, out_lon_rad * bst::math::R2D);
}

double distance(const Point &a, const Point &b) {
  double decimal_long = (b.longitude() - a.longitude()) * bst::math::D2R;
  double decimal_lat = (b.latitude() - a.latitude()) * bst::math::D2R;
  double a_calc = std::pow(sin(decimal_lat / 2.0), 2) +
                  std::cos(a.latitude() * bst::math::D2R) *
                      std::cos(b.latitude() * bst::math::D2R) *
                      std::pow(sin(decimal_long / 2.0), 2);
  double c = 2 * std::atan2(std::sqrt(a_calc), std::sqrt(1 - a_calc));
  double d = 6367 * c;

  return d;
}

Path::Path() : points_() {
}

Path::Path(std::vector<Point> points) : points_(points) {
}

double Path::distance() const {
  double distance = 0.0;
  for (size_t i = 0; i < points_.size() - 1; i++) {
    distance += bst::geo::distance(points_[i], points_[i + 1]);
  }
  return distance;
}

bool Path::getLastPoint(Point &point) const {
  if (points_.size() > 0) {
    point = points_.back();
    return true;
  }
  return false;
}

bool Path::getFirstPoint(Point &point) const {
  if (points_.size() > 0) {
    point = points_.front();
    return true;
  }
  return false;
}

} // namespace bst::geo