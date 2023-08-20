#include <Bst/exception.hpp>
#include <Bst/geo.hpp>

namespace BoosterSeat {

geo::Point::Point() : lat(0.0), lon(0.0) {
}

geo::Point::Point(double lat, double lon) : lat(lat), lon(lon) {
  // just going to roll with it i guess
  if (lat < -90.0 || lat > 90.0) {
#ifndef BOOSTERSEAT_NO_EXCEPTIONS
    throw BoosterSeatException("Latitude must be between -90.0 and 90.0",
                               ErrorNumber::GEO_INVALID_LATITUDE);
#endif
  }
#ifndef BOOSTERSEAT_NO_EXCEPTIONS
  if (lon < -180.0 || lon > 180.0) {
    throw BoosterSeatException("Longitude must be between -180.0 and 180.0",
                               ErrorNumber::GEO_INVALID_LONGITUDE);
  }
#endif
}

} // namespace BoosterSeat