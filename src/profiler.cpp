/// @file profiler.cpp
/// @author Joshua Jerred (https://joshuajer.red)
/// @brief Profiler class implementation
/// @date 2025-02-15
/// @copyright Copyright (c) 2025

#include <BoosterSeat/profiler.hpp>

namespace bst {

std::mutex Profiler::results_mutex_;

std::map<std::string, Profiler::Result> Profiler::results_;

} // namespace bst