#include <BoosterSeat/profiler.hpp>

#include <iostream>
#include <sstream>

#include "gtest/gtest.h"

TEST(bst_profiler, Event_StartStopTime) {
  bst::StaticTimeSource time_source;
  bst::Profiler::EventServicer servicer{time_source};

  time_source.setTicksNs(100);
  bst::Profiler::Event event{"event"};
  time_source.setTicksNs(201);
  event.stop();

  EXPECT_EQ(event.getStartTimeUs(), 100);
  EXPECT_EQ(event.getStopTimeUs(), 201);
  EXPECT_EQ(event.getDurationUs(), 101);

  const auto results = event.getResults();
  EXPECT_EQ(results.event_name, "event");
  EXPECT_EQ(results.start_time, 100);
  EXPECT_EQ(results.stop_time, 201);
}

TEST(bst_profiler, Event_Reporting) {
  using Event = bst::Profiler::Event;
  using Results = bst::Profiler::Event::Results;

  bst::StaticTimeSource time_source;
  bst::Profiler::EventServicer servicer{time_source};

  {
    time_source.setTicksNs(1);
    Event event1{"event1"};
    time_source.setTicksNs(2);
    Event event2{"event2"};
    time_source.setTicksNs(3);
    {
      Event event3{"event3"};
      time_source.setTicksNs(4);
    }
    time_source.setTicksNs(5);
    Event event4{"event4"};
    time_source.setTicksNs(6);
  }
  time_source.setTicksNs(7); // ignored

  const std::array<bst::Profiler::Event::Results, 4> expected{
      Results{"event1", 1, 6},
      Results{"event2", 2, 6},
      Results{"event3", 3, 4},
      Results{"event4", 5, 6},
  };

  auto reports = servicer.getEventReports();
  ASSERT_EQ(reports.size(), 4);

  for (const auto &report : reports) {
    bool found = false;
    for (const auto &expected_report : expected) {
      if (report.event_name == expected_report.event_name) {
        EXPECT_EQ(report.start_time, expected_report.start_time);
        EXPECT_EQ(report.stop_time, expected_report.stop_time);
        found = true;
        break;
      }
    }
    EXPECT_TRUE(found);
  }

  servicer.printResultsToStream(std::cout);
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