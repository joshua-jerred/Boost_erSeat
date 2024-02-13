# [BST module] Geo

The BoosterSeat geo module provides tools for working with geographic data.

## Geo Point

A simple class for representing a point on the earth's surface.

```cpp
#include <BoosterSeat/geo.hpp>
#include <iostream>

int main() {
  bst::geo::Point p1(38.889200, -77.050114);
  std::cout << p1.latitude() << ", " << p1.longitude() << std::endl;

  bst::geo::Point p2(38.889475, -77.035253);
  std::cout << bst::geo::distance(p1, p2) << std::endl;

  double bearing = 88.63;
  double distance_km = 1.28964;
  bst::geo::Point p3 = p1.shootVector(bearing, distance_km);

  return 0;
}

```

## Geo Path
```cpp
#include <BoosterSeat/geo.hpp>
#include <iostream>
#include <vector>

int main() {
  std::vector<bst::geo::Point> points = {{-35.6240233453558, -160.6826134328059},
                                         {-32.14417025725855, -156.9190554594102},
                                         {-26.74568499863755, -157.3440121164353},
                                         {-17.70743989126965, -151.5654080823589},
                                         {-14.83054253114009, -137.9579193031041}};

  bst::geo::Path path(points);

  std::cout << path.distance() << std::endl;

  // other wonderful methods:
  // bool path.getLastPoint(Point& p);
  // bool path.getFirstPoint(Point& p);

  return 0;
}

```