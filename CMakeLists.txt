cmake_minimum_required(VERSION 3.14)

project(BoosterSeat VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wpedantic -Wno-unused-parameter")

set(SOURCE_FILES 
  src/stopwatch.cpp
  src/string_format.cpp
  src/time.cpp
  src/filesystem.cpp
  src/random.cpp
)

add_library(BoosterSeat STATIC)
target_include_directories(BoosterSeat PUBLIC include)
target_sources(BoosterSeat PRIVATE ${SOURCE_FILES})

add_subdirectory(tests)