/// @file event.cpp
/// @author Joshua Jerred (https://joshuajer.red)
/// @brief Profiler Event class implementation
/// @date 2025-02-15
/// @copyright Copyright (c) 2025

#include <BoosterSeat/profiler.hpp>

namespace bst {

namespace Profiler {

Event::Event(const std::string &event_name, bool auto_start)
    : event_name_{event_name} {
  if (auto_start) {
    start();
  }
}

Event::~Event() {
  if (!event_stopped_) {
    stop();
  }
}

void Event::start() {
  if (event_started_) {
    throw BstException("event already started: " + event_name_,
                       ErrorNumber::PROFILER_EVENT);
  }

  event_started_ = true;
  start_time_ns_ = EventServicer::getTimestampNs();
}

void Event::stop() {
  if (event_stopped_) {
    throw BstException("event already stopped: " + event_name_,
                       ErrorNumber::PROFILER_EVENT);
  }

  assertEventStarted(); // We can't stop if we never started

  event_stopped_ = true;
  stop_time_ns_ = EventServicer::getTimestampNs();

  EventServicer::eventReport(getResults());
}

std::string Event::getEventName() const {
  return event_name_;
}

uint32_t Event::getStartTimeNs() const {
  assertEventStarted();
  return start_time_ns_;
}

uint32_t Event::getStopTimeNs() const {
  assertEventStopped();
  return stop_time_ns_;
}

uint32_t Event::getDurationNs() const {
  assertEventStarted();
  assertEventStopped();
  return stop_time_ns_ - start_time_ns_;
}

Event::Results Event::getResults() const {
  assertEventStarted();
  assertEventStopped();
  return {event_name_, start_time_ns_, stop_time_ns_};
}

void Event::assertEventStarted() const {
  if (!event_started_) {
    throw BstException("event not started: " + event_name_,
                       ErrorNumber::PROFILER_EVENT);
  }
}

void Event::assertEventStopped() const {
  if (!event_stopped_) {
    throw BstException("event not stopped: " + event_name_,
                       ErrorNumber::PROFILER_EVENT);
  }
}

} // namespace Profiler

} // namespace bst