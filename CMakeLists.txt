cmake_minimum_required(VERSION 3.14)

project(BoosterSeat VERSION 1.0)

## Check if SignalEasel is being used directly or via add_subdirectory
set(MAIN_PROJECT OFF)
if (CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    set(MAIN_PROJECT ON)
endif()
message(STATUS "=== BoosterSeat Main project: ${MAIN_PROJECT}")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wpedantic -Wno-unused-parameter")

set(ALL_SOURCE_FILES
  src/stopwatch.cpp
  src/string_format.cpp
  src/time.cpp
  src/filesystem.cpp
  src/random.cpp
  src/timer.cpp
  src/rolling_average.cpp
  src/numbers.cpp
  src/geo/geo_point.cpp
  #src/geo/geo_strings.cpp
)

add_library(BoosterSeat STATIC)
target_include_directories(BoosterSeat PUBLIC include)
target_sources(BoosterSeat PRIVATE ${ALL_SOURCE_FILES})

add_subdirectory(tests)