include(FetchContent)
FetchContent_Declare(
	googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
	)
FetchContent_MakeAvailable(googletest)
include(GoogleTest)

add_executable(stopwatch_test
  stopwatch_test.cpp
)
target_link_libraries(stopwatch_test BoosterSeat gtest_main)

add_executable(string_format_test
  string_format_test.cpp
)
target_link_libraries(string_format_test BoosterSeat)

add_executable(visual_tests
  visual_tests.cpp
)
target_link_libraries(visual_tests BoosterSeat)

add_executable(filesystem_test
  filesystem_test.cpp
)
target_link_libraries(filesystem_test BoosterSeat gtest_main)

add_executable(rolling_average_test
  rolling_average_test.cpp
)
target_link_libraries(rolling_average_test BoosterSeat gtest_main)