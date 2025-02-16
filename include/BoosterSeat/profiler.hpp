/// @file profiler.hpp
/// @author Joshua Jerred (https://joshuajer.red)
/// @brief A
/// @date 2025-02-15
/// @copyright Copyright (c) 2025

#pragma once

/// @todo remove iostream
#include <atomic>
#include <iostream>
#include <mutex>
#include <span>
#include <string>
#include <vector>

#include <BoosterSeat/exception.hpp>
#include <bst/time_source.hpp>

namespace bst {

/// @brief The Profiler namespace which contains classes to help do timing
/// analysis on code.
/// @warning The Profiler namespace is not thread safe and very
/// experimental.
namespace Profiler {

/// @brief A class to represent a unit of code/work to be profiler.
/// @details By default, the event start/stop times are recorded automatically
/// upon construction/destruction of the object. This way, a user can simply
/// instantiate an Event object with a name and the scope time will be recorded.
class Event;

/// @brief An class that services event start/stop data reports and provide a
/// time source for the events.
class EventServicer;

/// @brief A class to process the results of the events received by the event
/// servicer.
class ReportGenerator;

class Event {
public:
  /// @brief Construct a new Event object and starts the event
  /// @param event_name - The name of the even, used for output.
  /// @param auto_start - Automatically start the event. Defaults to true.
  Event(const std::string &event_name, bool auto_start = true);

  /// @brief Destructor: stops the event if it hasn't been stopped manually
  /// (irregular use case) by the user.
  ~Event();

  /// @brief The results of the event that are reported to the EventServicer
  struct Results {
    /// @brief The name of the event
    std::string event_name;
    /// @brief The start time of the event
    uint32_t start_time;
    /// @brief The stop time of the event
    uint32_t stop_time;
  };

  /// @brief (Called Automatically) Record the start time of the event
  /// @details With the default arguments, this method is called automatically
  /// upon construction.
  void start();

  /// @brief (Called Automatically) Record the stop time of the event
  /// @details This method is called upon destruction of the event object.
  /// Manually calling this method should be avoided,
  void stop();

  std::string getEventName() const;

  uint32_t getStartTimeNs() const;

  uint32_t getStopTimeNs() const;

  uint32_t getDurationNs() const;

  /// @brief Get the results data structure for the event
  Results getResults() const;

private:
  /// @brief The name of the event, used for output
  const std::string event_name_;

  /// @brief The start time of the event, set by start()
  uint32_t start_time_ns_{0};

  /// @brief The end time of the event, set by stop()
  uint32_t stop_time_ns_{0};

  /// @brief Flag to ensure the event is only started once
  bool event_started_{false};
  /// @brief Flag to ensure the event is only stopped once
  bool event_stopped_{false};
  /// @brief Ensure the event has been started
  void assertEventStarted() const;
  /// @brief Ensure the event has been stopped
  void assertEventStopped() const;
};

class EventServicer {
public:
  EventServicer(ITimeSource &time_source) : time_source_{time_source} {
    bool was_initialized = initialized_.exchange(true);
    if (was_initialized) {
      throw BstException("EventServicer already initialized",
                         ErrorNumber::PROFILER);
    }

    instance_ = this;
  }

  ~EventServicer() {
    if (initialized_) {
      initialized_ = false;
    }
  }

  /// @brief Get the event reports in the order that they were reported
  /// @return A vector of event reports
  const std::vector<Event::Results> getEventReports() const {
    return event_reports_;
  }

private:
  // Friend Event to allow access to getTimestampUs() and eventReport()
  friend class Event;

  /// @brief Used by events to get their start/stop times.
  /// @warning The time reference is up to the implementation, it does not have
  /// to be the system time.
  static uint32_t getTimestampNs() {
    assertInitialized();
    return instance_->time_source_.getTicksNs();
  }

  /// @brief Used by events to report their start/stop times.
  /// @param event_name - The name of the event
  /// @param start_time - The start time of the event
  /// @param stop_time - The stop time of the event
  static void eventReport(const Event::Results &results) {
    assertInitialized();
    instance_->eventReportHandler(results);
  }

  static void assertInitialized() {
    if (!initialized_) {
      throw BstException("EventServicer not initialized",
                         ErrorNumber::PROFILER);
    }
  }

  void eventReportHandler(const Event::Results &results) {
    event_reports_.push_back(results);
  }

  /// @brief Flag to ensure the EventServicer is only initialized once
  static std::atomic<bool> initialized_;

  /// @brief Pointer to the instance of the EventServicer
  static EventServicer *instance_;

  /// @brief The time source for the events
  ITimeSource &time_source_;

  /// @brief The reports of the events, ordered by first stopped to last.
  std::vector<Event::Results> event_reports_;
};

struct ReportOptions {
  /// @brief [default=true] - Scale the time from nanoseconds to the most
  /// readable format. If false, the time will be in only nanoseconds.
  bool scale_time_to_ms{true};

  /// @brief [default=true] - Reindex the time to start at 0. If false and using
  /// system time, the results will not be human readable.
  bool reindex_time{true};

  // CSV Options
  bool include_header{true};
};

class ReportGenerator {
public:
  ReportGenerator(const EventServicer &servicer,
                  ReportOptions options = ReportOptions{})
      : servicer_{servicer}, options_{options} {
  }

  /// @brief Generate a CSV report of the events
  /// @param servicer - The EventServicer to get the event reports from
  /// @param os - The output stream to write the CSV report to
  /// @param include_header [default=true] - Include the header in the CSV
  /// report.
  /// @param scale_time_to_ms [default=true] - Scale the time to the 'most
  /// readable' format
  void generateCsvReport(std::ostream &os);

private:
  /// @brief Scale the time to the 'most readable' format
  std::string scaleTime(uint64_t time_ns);

  std::string percentageOfTotal(uint64_t time_ns);

  /// @brief Parse the results and generate the necessary data structures for
  /// generating the report.
  /// @param servicer - The EventServicer to get the event reports from
  void processResults();

  /// @brief The minimum start time of the events. Set by processResults()
  uint64_t minimum_start_time_{0};
  /// @brief The maximum stop time of the events. Set by processResults()
  uint64_t maximum_stop_time_{0};
  /// @brief The total duration of all the events. Set by processResults()
  uint64_t total_duration_{0};

  /// @brief The EventServicer to get the event reports from
  const EventServicer &servicer_;

  /// @brief The options for the report
  const ReportOptions options_;
};

} // namespace Profiler
} // namespace bst