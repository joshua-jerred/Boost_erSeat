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

add_executable(time_output_test
  time_output_test.cpp
)
target_link_libraries(time_output_test BoosterSeat)