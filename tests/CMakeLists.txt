# Visual tests
add_executable(visual_tests
  visual_tests.cpp
)
target_link_libraries(visual_tests BoosterSeat)

# Unit tests
include(FetchContent)
FetchContent_Declare(
	googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.14.0)
FetchContent_MakeAvailable(googletest)

add_executable(unit_tests
  filesystem_test.cpp
  filters_test.cpp
  geo_test.cpp
  process_test.cpp
  random_test.cpp
  rolling_average_test.cpp
  science_test.cpp
  stopwatch_test.cpp
  string_format_test.cpp
  time_class_test.cpp
  timer_test.cpp
)
target_link_libraries(unit_tests 
  BoosterSeat
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(unit_tests)