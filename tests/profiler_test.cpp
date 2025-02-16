#include <BoosterSeat/profiler.hpp>
#include <BoosterSeat/sleep.hpp>

#include <iostream>
#include <sstream>

#include "gtest/gtest.h"

TEST(bst_profiler, EventStartStop) {
  // bst::Profiler profiler{"test_profiler_1"};

  {
    // bst::Profiler::Event event{"event_1"};
    // bst::sleep(10);
  }
}

// TEST(bst_profiler, UseCaseTest) {
//   bst::Profiler profiler{"test_profiler_1"};

//   {
//     bst::Profiler::Event event{"event_1"};
//     bst::sleep(10);
//     bst::Profiler::Event event2{"event_2"};
//     bst::sleep(10);
//   }

//   // bst::sleep(10);

//   // profiler.event("event_1");
//   // bst::sleep(10);
//   // profiler.event("event_2");
// }