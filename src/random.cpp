#include <BoosterSeat/random.hpp>


std::string BoosterSeat::randomHexString(unsigned int length) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(0, 15);

  std::string str(length, '0');
  for (auto& chr : str) {
    chr = "0123456789abcdef"[dis(gen)];
  }
  return str;
}