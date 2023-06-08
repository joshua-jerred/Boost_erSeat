// just a simple visual test

#include <BoosterSeat/sleep.hpp>
#include <BoosterSeat/time.hpp>
#include <iostream>

namespace bst = BoosterSeat::time;

int main() {
  // Without delimiter argument
  std::cout << "without delimiter argument" << std::endl;
  std::cout << "timeString UTC   | " << bst::timeString(bst::TimeZone::UTC)
            << std::endl;
  std::cout << "timeString Local | " << bst::timeString() << std::endl;
  std::cout << "dateString Local | " << bst::dateString() << std::endl;
  std::cout << std::endl;

  // With delimiter argument
  std::cout << "with delimiter argument" << std::endl;
  std::cout << "timeString UTC   | " << bst::timeString(bst::TimeZone::UTC, '/')
            << std::endl;
  std::cout << "timeString Local | "
            << bst::timeString(bst::TimeZone::LOCAL, '/') << std::endl;
  std::cout << "dateString Local | "
            << bst::dateString(bst::TimeZone::LOCAL, '/') << std::endl;
  std::cout << std::endl;

  // With delimiter argument
  std::cout << "with null delimiter argument" << std::endl;
  std::cout << "timeString UTC   | "
            << bst::timeString(bst::TimeZone::UTC, '\0') << std::endl;
  std::cout << "timeString Local | "
            << bst::timeString(bst::TimeZone::LOCAL, '\0') << std::endl;
  std::cout << "dateString Local | "
            << bst::dateString(bst::TimeZone::LOCAL, '\0') << std::endl;
  std::cout << std::endl;

  // getDateAndTimeStr
  std::cout << "getDateAndTimeStr | " << BoosterSeat::time::dateAndTimeString()
            << std::endl;
  std::cout << "getDateAndTimeStr | "
            << BoosterSeat::time::dateAndTimeString(bst::TimeZone::UTC, '*',
                                                    '$', '#')
            << std::endl;
  std::cout << std::endl;

  // elapsedAsciiClock
  std::cout << "elapsedAsciiClock" << std::endl;
  auto time_point = BoosterSeat::clck::now();
  std::cout << "elapsedAsciiClock | "
            << BoosterSeat::time::elapsedAsciiClock(time_point) << std::endl;
  BoosterSeat::util::sleep(1000);
  std::cout << "elapsedAsciiClock | "
            << BoosterSeat::time::elapsedAsciiClock(time_point) << std::endl;

  return 0;
}
