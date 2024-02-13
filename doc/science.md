# [BST module] Science

A collection of physics, environmental, and other tools.

```cpp
#include <BoosterSeat/science.hpp>
```

## Constants
```cpp
bst::K_GRAVITY // Standard Gravitational constant
```

## Pressure Conversions

### `bst::Pressure` class
```cpp
  bst::Pressure(); // only has a default constructor, set to 0 pascals

  void setFromPascals(double pascals);
  double pascals() const;

  void setFromMillibars(double millibars);
  double millibars() const;

  void setFromInchesMercury(double inches_mercury);
  double inchesMercury() const;

  void setFromPSI(double psi);
  double psi() const;

  void setFromAtmospheres(double atmospheres);
  double atmospheres() const;
```

### Example
```cpp
#include <iostream>
#include <BoosterSeat/science.hpp>

int main() {
  bst::Pressure p;

  p.setFromPascals(100000);
  std::cout << "Pascals: " << p.pascals() << std::endl;
  std::cout << "Millibars: " << p.millibars() << std::endl;
  std::cout << "Inches Mercury: " << p.inchesMercury() << std::endl;
  std::cout << "PSI: " << p.psi() << std::endl;
  std::cout << "Atmospheres: " << p.atmospheres() << std::endl;

  return 0;
}
```
```bash
$ ./example
Pascals: 100000
Millibars: 1000
Inches Mercury: 29.53
PSI: 14.5038
Atmospheres: 0.986923
```
