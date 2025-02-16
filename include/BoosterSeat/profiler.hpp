/// @file profiler.hpp
/// @author Joshua Jerred (https://joshuajer.red)
/// @brief A
/// @date 2025-02-15
/// @copyright Copyright (c) 2025

#pragma once

/// @todo remove iostream
#include <iostream>
#include <map>
#include <mutex>
#include <string>

#include <BoosterSeat/exception.hpp>

#include <bst/time_source.hpp>

namespace bst {

/// @brief The Profiler namespace which contains classes to help do timing
/// analysis on code.
namespace Profiler {

/// @brief An class that services event start/stop data reports and provide a
/// time source for the events.
class EventServicer {
public:
  /// @brief Used by events to get their start/stop times.
  /// @warning The time reference is up to the implementation, it does not have
  /// to be the system time.
  static uint32_t getTimestampUs() {
    return 0;
  }

  /// @brief Used by events to report their start/stop times.
  /// @param event_name - The name of the event
  /// @param start_time - The start time of the event
  /// @param stop_time - The stop time of the event
  static void eventReport(const std::string &event_name, uint32_t start_time,
                          uint32_t stop_time) {
    std::cout << "Event: " << event_name << " started at: " << start_time
              << " and stopped at: " << stop_time << std::endl;
  }
};

/// @brief A class to represent a unit of code/work to be profiler.
/// @details By default, the event start/stop times are recorded automatically
/// upon construction/destruction of the object. This way, a user can simply
/// instantiate an Event object with a name and the scope time will be recorded.
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