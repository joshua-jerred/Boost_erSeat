/// @file profiler.cpp
/// @author Joshua Jerred (https://joshuajer.red)
/// @brief Profiler class implementation
/// @date 2025-02-15
/// @copyright Copyright (c) 2025

#include <BoosterSeat/profiler.hpp>

namespace bst {

void Profiler::Event::start() {
  if (event_started_) {
    throw BstException("event already started: " + event_name_,
                       ErrorNumber::PROFILER_EVENT);
  }

  event_started_ = true;
  start_time_us_ = EventServicer::getTimestampNs();
}

void Profiler::Event::stop() {
  if (event_stopped_) {
    throw BstException("event already stopped: " + event_name_,
                       ErrorNumber::PROFILER_EVENT);
  }

  assertEventStarted(); // We can't stop if we never started

  event_stopped_ = true;
  stop_time_us_ = EventServicer::getTimestampNs();

  // Report the event data to the EventServicer (which can be mocked/stubbed)
  EventServicer::eventReport(event_name_, start_time_us_, stop_time_us_);
}

uint32_t Profiler::Event::getStartTimeUs() const {
  assertEventStarted();
  return start_time_us_;
}

uint32_t Profiler::Event::getStopTimeUs() const {
  assertEventStopped();
  return stop_time_us_;
}

uint32_t Profiler::Event::getDurationUs() const {
  assertEventStarted();
  assertEventStopped();
  return stop_time_us_ - start_time_us_;
}

void Profiler::Event::assertEventStarted() const {
  if (!event_started_) {
    throw BstException("event not started: " + event_name_,
                       ErrorNumber::PROFILER_EVENT);
  }
}

void Profiler::Event::assertEventStopped() const {
  if (!event_stopped_) {
    throw BstException("event not stopped: " + event_name_,
                       ErrorNumber::PROFILER_EVENT);
  }
}

// static members of Profiler
// std::mutex Profiler::results_mutex_;
// std::map<std::string, Profiler::Result> Profiler::results_;
std::atomic<bool> Profiler::EventServicer::initialized_{false};
Profiler::EventServicer *Profiler::EventServicer::instance_{nullptr};

} // namespace bst