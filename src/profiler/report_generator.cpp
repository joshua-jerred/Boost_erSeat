/// @file report_generator.cpp
/// @author Joshua Jerred (https://joshuajer.red)
/// @brief
/// @date 2025-02-15
/// @copyright Copyright (c) 2025

#include <BoosterSeat/profiler.hpp>

namespace bst {

namespace Profiler {

void ReportGenerator::eventCsv(EventServicer &servicer, std::ostream &os,
                               ReportOptions options) {
  auto reports = servicer.getEventReports();

  os << "event_name,start_time_ns,stop_time_ns,elapsed_time_ns\n";
  for (const auto &report : reports) {
    os << report.event_name << "," << report.start_time << ","
       << report.stop_time << "," << report.stop_time - report.start_time
       << "\n";
  }
}

} // namespace Profiler

} // namespace bst