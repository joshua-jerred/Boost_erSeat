#include <BoosterSeat/geo.hpp>
#include <BoosterSeat/geo_strings.hpp>
#include <BoosterSeat/numbers.hpp>

namespace BoosterSeat {

inline constexpr int kPrecision = 6;

std::ostream &geo::operator<<(std::ostream &os, const geo::Point &point) {
  os << "Point(" << rndTs(point.lat, kPrecision) << ", "
     << rndTs(point.lon, kPrecision) << ")";
  return os;
}

} // namespace BoosterSeat