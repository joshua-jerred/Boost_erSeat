#include <BoosterSeat/sleep.hpp>
#include <bst/time_source.hpp>

#include <chrono>

#include "gtest/gtest.h"

TEST(bst_TimeSource, HighResolutionTimeSource_sameAsSystemTime) {
  bst::HighResolutionTimeSource time_source;

  const uint64_t reported_time = time_source.getTicksNs();

  const uint64_t expected_time =
      std::chrono::duration_cast<std::chrono::milliseconds>(
          std::chrono::system_clock::now().time_since_epoch())
          .count();

  EXPECT_GE(reported_time, expected_time - 1000)
      << "reported: " << reported_time << " expected: " << expected_time;
}

TEST(bst_TimeSource, HighResolutionTimeSource_increments) {
  bst::HighResolutionTimeSource time_source;

  const uint64_t start_time_ns = time_source.getTicksNs();
  bst::sleep(1); // sleep for 1 ms
  const uint64_t end_time_ns = time_source.getTicksNs();

  EXPECT_GT(end_time_ns, start_time_ns);
}