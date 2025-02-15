/// @file profiler.hpp
/// @author Joshua Jerred (https://joshuajer.red)
/// @brief A
/// @date 2025-02-15
/// @copyright Copyright (c) 2025

#pragma once

#include <map>
#include <mutex>
#include <string>

#include <BoosterSeat/exception.hpp>

namespace bst {

class Profiler {
public:
  /// @brief The result of a profiler run
  struct Result {
    /// @brief Sanity check to ensure the profiler is used correctly
    bool complete{false};

    /// @brief The number of microseconds from construction to destruction
    uint32_t microseconds{0};
  };

  class Event {
  public:
    /// @brief Construct a new Event object and starts the event
    /// @param event_name
    Event(const std::string &event_name) : event_name_{event_name} {
      start();
    }

    ~Event() {
      if (!complete_) { // check if complete here, not in stop(). stop() will
                        // enforce that it is only called once
        stop();
      }
    }

    /// @brief Stop the event early
    /// @details Normally the event will start upon construction and stop upon
    /// destruction. This method allows the user to stop the event early. This
    /// is just semantics to show the ideal implementation of the profiler.
    void stopEarly() {
      stop();
    }

    uint32_t getStartTimeUs() const {
      return start_time_us_;
    }

    uint32_t getEndTimeUs() const {
      if (!complete_) {
        throw bst::BoosterSeatException("event not stopped: " + event_name_,
                                        bst::ErrorNumber::PROFILER_EVENT);
      }
      return end_time_us_;
    }

    uint32_t getDurationUs() const {
      if (!complete_) {
        throw bst::BoosterSeatException("event not stopped: " + event_name_,
                                        bst::ErrorNumber::PROFILER_EVENT);
      }
      return end_time_us_ - start_time_us_;
    }

  private:
    void start() {
      // start the event
    }

    void stop() {
      // Ensure that stop is only called once
      if (complete_) {
        throw bst::BoosterSeatException("event already stopped: " + event_name_,
                                        bst::ErrorNumber::PROFILER_EVENT);
      }
      complete_ = true;
    }

    bool complete_{false};

    /// @brief The start time of the event, set upon construction.
    const uint32_t start_time_us_;

    uint32_t end_time_us_{0};

    const std::string event_name_;
  };

  Profiler(const std::string &name) : name_{name} {
    std::lock_guard<std::mutex> lock(results_mutex_);
  }

  ~Profiler() {
    // stopProfiling();
  }

  static uint32_t getCurrentTimeUs() {
    return 0;
  }

private:
  /// @brief The name of this profiler
  const std::string name_;

  /// @brief Mutex to protect the results_ map
  static std::mutex results_mutex_;

  /// @brief A map of profiler results, keyed by the name of the profiler
  static std::map<std::string, Result> results_;
};
} // namespace bst