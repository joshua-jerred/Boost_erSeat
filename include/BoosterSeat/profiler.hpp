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

class Event {
public:
  /// @brief Construct a new Event object and starts the event
  /// @param event_name - The name of the even, used for output.
  /// @param auto_start - Automatically start the event. Defaults to true.
  Event(const std::string &event_name, bool auto_start = true)
      : event_name_{event_name} {
    if (auto_start) {
      start();
    }
  }

  /// @brief Destructor: stops the event if it hasn't been stopped manually
  /// (irregular use case) by the user.
  ~Event() {
    if (!event_stopped_) {
      stop();
    }
  }

  /// @brief (Called Automatically) Record the start time of the event
  /// @details With the default arguments, this method is called automatically
  /// upon construction.
  /// @exception bst::BoosterSeatException - If the event has already been
  /// started.
  void start();

  /// @brief (Called Automatically) Record the stop time of the event
  /// @details This method is called upon destruction of the event object.
  /// Manually calling this method should be avoided,
  void stop();

  uint32_t getStartTimeUs() const;

  uint32_t getStopTimeUs() const;

  uint32_t getDurationUs() const;

private:
  /// @brief The name of the event, used for output
  const std::string event_name_;

  /// @brief The start time of the event, set by start()
  uint32_t start_time_us_{0};

  /// @brief The end time of the event, set by stop()
  uint32_t stop_time_us_{0};

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
                         ErrorNumber::PROFILER_EVENT);
    }

    instance_ = this;
  }

  ~EventServicer() {
    if (initialized_) {
      initialized_ = false;
    }
  }

  struct Results {
    std::string event_name;
    uint32_t start_time;
    uint32_t stop_time;
  };

  /// @brief Get the event reports in the order that they were reported
  /// @return A vector of event reports
  const std::vector<Results> getEventReports() const {
    return event_reports_;
  }

  /// @brief Simple factory method to create a new event that automatically
  /// starts
  /// @param event_name - The name of the event
  /// @return Event - The new event
  static Event NewEvent(const std::string &event_name) {
    return Event(event_name);
  }

  /// @brief Print the results to a stream, in non-hierarchical format (results
  /// array).
  void printResultsToStream(std::ostream &os) const {
    for (const auto &report : event_reports_) {
      os << report.event_name << ": " << report.start_time << "ns - "
         << report.stop_time << "ns" << std::endl;
    }
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
  static void eventReport(const std::string &event_name, uint32_t start_time,
                          uint32_t stop_time) {
    assertInitialized();

    Results results{
        .event_name = event_name,
        .start_time = start_time,
        .stop_time = stop_time,
    };

    instance_->eventReportHandler(results);
  }

  static void assertInitialized() {
    if (!initialized_) {
      throw BstException("EventServicer not initialized",
                         ErrorNumber::PROFILER_EVENT);
    }
  }

  void eventReportHandler(Results &results) {
    event_reports_.push_back(results);
  }

  /// @brief Flag to ensure the EventServicer is only initialized once
  static std::atomic<bool> initialized_;

  /// @brief Pointer to the instance of the EventServicer
  static EventServicer *instance_;

  /// @brief The time source for the events
  ITimeSource &time_source_;

  /// @brief A map of event reports, keyed by the name of the event
  std::vector<Results> event_reports_;
};

// class Profiler {
// public:
//   /// @brief The result of a profiler run
//   // struct Result {
//   //   /// @brief Sanity check to ensure the profiler is used correctly
//   //   bool complete{false};

//   //   /// @brief The number of microseconds from construction to
//   destruction
//   //   uint32_t microseconds{0};
//   // };

//   Profiler(const std::string &name) : name_{name} {
//     std::lock_guard<std::mutex> lock(results_mutex_);
//   }

//   ~Profiler() {
//     // stopProfiling();
//   }

//   static uint32_t getCurrentTimeUs() {
//     return 0;
//   }

// private:
//   /// @brief The name of this profiler
//   const std::string name_;

//   /// @brief Mutex to protect the results_ map
//   static std::mutex results_mutex_;

//   /// @brief A map of profiler results, keyed by the name of the profiler
//   // static std::map<std::string, Result> results_;
// };

} // namespace Profiler
} // namespace bst