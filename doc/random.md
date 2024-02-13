# [BST module] Random

A simple set of random value generators.

## Functions
```cpp
#include <BoosterSeat/random.hpp>

bst::randomHexString(size_t length);
bst::randomDouble(double min, double max);
```

## Examples:

### Random hex string
```cpp
#include <BoosterSeat/random.hpp>
#include <iostream>

int main() {
  // Generate a random hex string of length 16
  std::cout << bst::randomHexString(16) << std::endl;
  return 0;
}
```
```sh
$ ./example
a13449fbb09e2bf0
```

## Random Double
```cpp
#include <BoosterSeat/random.hpp>
#include <iostream>

int main() {
  double min = 0.0;
  double max = 1.0;
  std::cout << bst::randomDouble(min, max) << std::endl;
}
```
```sh
$ ./example
0.3565
```