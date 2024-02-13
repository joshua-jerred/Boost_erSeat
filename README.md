it's just like boost, but has none of the features

This is just my set of helpful C++ utilities that I use across many projects.

***

# Modules
- [`<BoosterSeat/process.hpp>`](https://bst.joshuajer.red/md_doc_process.html)
  - a nice C++ wrapper to run linux commands
  - detailed documentation can be found [here](https://bst.joshuajer.red/md_doc_process.html)
- `<BoosterSeat/clock.hpp>`
  - Just a wrapper on `<chrono>` with typedefs that I am always searching for.
- `<BoosterSeat/numbers.hpp>`
  - dealing with numbers
- `<BoosterSeat/rolling_average.hpp>`
  - for calculating a rolling average
- `<BoosterSeat/timer.hpp>`
  - for timing intervals
- `<BoosterSeat/filesystem.hpp>`
  - a simple and cautious wrapper around `<filesystem>`
- `<BoosterSeat/random.hpp>`
  - random number/string generation

***

# Using with CMake
Clone the repo into a project:

```bash
cd your_project/third_party_libs
git clone git@github.com:joshua-jerred/Boost_erSeat.git
```


Add the following to `your_project/CMakeLists.txt`:
```cmake
add_subdirectory(third_party_libs/Boost_erSeat)
target_link_libraries(<your_target> BoosterSeat)
```

Headers are taken care of for you, for example:
```cpp
#include <BoosterSeat/sleep.hpp>

int main() {
  bst::sleep(1000);
}
```