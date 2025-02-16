/// @file report_generator.cpp
/// @author Joshua Jerred (https://joshuajer.red)
/// @brief
/// @date 2025-02-15
/// @copyright Copyright (c) 2025

#include <iomanip>

#include <BoosterSeat/profiler.hpp>

namespace bst {

namespace Profiler {

void ReportGenerator::generateCsvReport(std::ostream &os) {
  processResults();
  auto reports = servicer_.getEventReports();

  os << "event_name,start_time,stop_time,elapsed_time,percentage_of_total\n";
  for (const auto &report : reports) {
    os << report.event_name << "," << scaleTime(report.start_time) << ","
       << scaleTime(report.stop_time) << ","
       << scaleTime(report.stop_time - report.start_time) << ","
       << percentageOfTotal(report.stop_time - report.start_time) << "\n";
  }
}

void ReportGenerator::processResults() {
  auto reports = servicer_.getEventReports();
  if (reports.empty()) {
    throw BstException("cannot generate report with no events",
                       ErrorNumber::PROFILER);
  }

  minimum_start_time_ = std::numeric_limits<uint64_t>::max();
  maximum_stop_time_ = 0;

  // Reverse order for future flame graph style tree processing
  for (auto it = reports.rbegin(); it != reports.rend(); ++it) {
    if (it->start_time < minimum_start_time_) {
      minimum_start_time_ = it->start_time;
    }

    if (it->stop_time > maximum_stop_time_) {
      maximum_stop_time_ = it->stop_time;
    }
  }

  total_duration_ = maximum_stop_time_ - minimum_start_time_;
}

std::string ReportGenerator::scaleTime(uint64_t time_ns) {
  if (options_.reindex_time && time_ns >= minimum_start_time_) {
    time_ns -= minimum_start_time_;
  }

  std::ostringstream ss;
  ss << std::fixed;

  if (options_.scale_time_to_ms) {
    double time_ms = static_cast<double>(time_ns) / 1e6;
    int precision = 0;
    if (time_ms <= 1) {
      precision = 3;
    } else if (time_ms <= 10) {
      precision = 2;
    } else if (time_ms <= 100) {
      precision = 1;
    }
    ss << std::setprecision(precision) << time_ms << "ms";
  } else {
    ss << (time_ns) << "ns";
  }

  return ss.str();
}

std::string ReportGenerator::percentageOfTotal(uint64_t time_ns) {
  double percentage = static_cast<double>(time_ns) / total_duration_ * 100;
  std::ostringstream ss;
  ss << std::fixed << std::setprecision(2) << percentage << "%";
  return ss.str();
}

} // namespace Profiler

} // namespace bst