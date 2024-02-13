/**
 * @file random.cpp
 * @author Joshua Jerred (https://joshuajer.red)
 * @brief Implementation of the BoosterSeat random module.
 * @date 2024-02-13
 * @copyright Copyright (c) 2024
 */

#include <random>

#include <BoosterSeat/random.hpp>

std::string bst::randomHexString(size_t length) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(0, 15);

  std::string str(length, '0');
  for (auto &chr : str) {
    chr = "0123456789abcdef"[dis(gen)];
  }
  return str;
}

double bst::randomDouble(double min, double max) {
  static std::random_device rd;
  static std::mt19937 gen(rd());
  std::uniform_real_distribution<double> dis(min, max);
  return dis(gen);
}