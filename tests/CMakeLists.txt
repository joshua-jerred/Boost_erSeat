include(FetchContent)
FetchContent_Declare(
	googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
	)
FetchContent_MakeAvailable(googletest)
include(GoogleTest)

add_executable(unit_tests
  stopwatch_test.cpp
  string_format_test.cpp
  filesystem_test.cpp
  rolling_average_test.cpp
  geo_test.cpp
  time_class_test.cpp
)
target_link_libraries(unit_tests BoosterSeat gtest_main)

add_executable(visual_tests
  visual_tests.cpp
)
target_link_libraries(visual_tests BoosterSeat)
