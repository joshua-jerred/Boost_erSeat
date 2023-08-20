it's just like boost, but has none of the features

This is just my set of helpful C++ utilities that I use across many projects.

Most of these things are not fully tested in any way.

***

# Using with CMake
Clone the repo into a project, and add the following to your `CMakeLists.txt`:
```
add_subdirectory(BoosterSeat)
target_link_libraries(<your target> BoosterSeat)
```

All includes are in `include/BoosterSeat/` but CMake will
take care of that for you.

***

# New Thing: Embedded Functionality

***

# What's included

### `<Bst/clock.hpp>`

- Just a wrapper on `<chrono>` with typedefs that I am always searching for.
  
```c++
using namespace BoosterSeat;

// std::chrono::duration typedefs
clck::units::Seconds;
clck::units::Milliseconds;
clck::units::Microseconds;

// clocks, timepoints, durations
clck::Clock;
clck::TimePoint;
clck::Duration;

// For dealing with 'TimePoint'(s)
inline TimePoint clck::now(); 
inline int clck::secondsElapsed(const TimePoint &time_point);
inline int clck::millisecondsElapsed(const TimePoint &time_point);

```


### `<Bst/numbers.hpp>`
- dealing with numbers

```c++
using namespace BoosterSeat;

// round a double (without strings being involved)
double doubleToPrecisionTwo(double);

// check if two numbers are approximately equal given an epsilon
inline bool isApproxEqual(double a, double b, double epsilon);

// check if two numbers are approximately equal given a percentage
inline bool isApproxEqualPercent(const double a, const double b,
                                 const double percent);

```

### `<Bst/rolling_average.hpp>`
- for calculating a rolling average

```c++
using namespace BoosterSeat;

// create a rolling average object
RollingAverage::RollingAverage(int window_size);

// add values to the rolling average within the window time
void RollingAverage::count(double count = 1.0);

// close the window and transition to a new window
void RollingAverage::intervalCall();

// get the current rolling average
double RollingAverage::getAverage() const;
```

### `<Bst/timer.hpp>`
- for timing intervals

```c++
using namespace BoosterSeat;

// create a timer object with a timeout
Timer(int timeout_ms);

// reset/restart the timer
void Timer::reset();

// check if the timer has timed out
bool Timer::isDone() const;

// change the timeout
void Timer::setTimeout(int timeout_ms);
```

## And more random things

### `<Bst/filesystem.hpp>`
- a simple and cautious wrapper around `<filesystem>`
### `<Bst/random.hpp>`
- random number/string generation

## And a few more
