#include <Bst/geo.hpp>
#include <Bst/geo_strings.hpp>
#include <Bst/numbers.hpp>

namespace BoosterSeat {

inline constexpr int kPrecision = 6;

std::ostream &geo::operator<<(std::ostream &os, const geo::Point &point) {
  os << "Point(" << rndTs(point.lat, kPrecision) << ", "
     << rndTs(point.lon, kPrecision) << ")";
  return os;
}

} // namespace BoosterSeat