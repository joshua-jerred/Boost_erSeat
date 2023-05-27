// just a simple visual test

#include <BoosterSeat/time.hpp>
#include <BoosterSeat/sleep.hpp>
#include <iostream>

int main() {
  std::cout << BoosterSeat::time::localTimeString() << std::endl;
  std::cout << BoosterSeat::time::utcTimeString() << std::endl;

  auto time_point = BoosterSeat::clck::now();
  std::cout << BoosterSeat::time::elapsedAsciiClock(time_point) << std::endl;
  BoosterSeat::util::sleep(1000);
  std::cout << BoosterSeat::time::elapsedAsciiClock(time_point) << std::endl;
  return 0;
}
