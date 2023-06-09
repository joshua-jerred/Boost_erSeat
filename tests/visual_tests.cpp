// just a simple visual test

#include <BoosterSeat/random.hpp>
#include <BoosterSeat/sleep.hpp>
#include <BoosterSeat/string_formatting.hpp>
#include <BoosterSeat/time.hpp>
#include <BoosterSeat/timer.hpp>
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
  BoosterSeat::threadSleep(1000);
  std::cout << "elapsedAsciiClock | "
            << BoosterSeat::time::elapsedAsciiClock(time_point) << std::endl;

  std::cout << std::endl;

  // dateAndTimeToTimePoint
  std::cout << "dateAndTimeToTimePoint | ";
  auto tp = BoosterSeat::time::dateAndTimeToTimePoint(2021, 2, 3, 4, 5, 6);
  std::cout << bst::dateAndTimeString(bst::TimeZone::LOCAL, '-', ' ', ':', tp)
            << std::endl;

  std::cout << std::endl;

  // random hex string
  std::cout << "random hex string | " << BoosterSeat::randomHexString(10)
            << std::endl;

  BoosterSeat::Timer timer(500);
  std::cout << "timer started" << std::endl;
  while (!timer.isDone()) {
    std::cout << "timer not done" << std::endl;
    BoosterSeat::threadSleep(100);
  }
  std::cout << "timer done" << std::endl;
  timer.reset();
  while (!timer.isDone()) {
    std::cout << "timer not done" << std::endl;
    BoosterSeat::threadSleep(100);
  }

  std::vector<std::vector<std::string>> out = {{"hello", "world", "this"},
                                               {"is", "a", "test"},
                                               {"of", "the", "emergency"},
                                               {"broadcast", "system", "!"}};

  BoosterSeat::layout::Alignment align = BoosterSeat::layout::Alignment::LEFT;
  int column_width = 15;

  std::cout << BoosterSeat::layout::simpleColumns(out, align, column_width);

  std::cout << std::endl;

  std::vector<std::string> row = {"hello", "there", "world"};
  align = BoosterSeat::layout::Alignment::CENTER;
  int row_width = 30;

  std::cout << BoosterSeat::layout::fixedWidthRow(row, align, row_width)
            << std::endl;
  std::cout << BoosterSeat::layout::fixedWidthString(
                   "hello", BoosterSeat::layout::Alignment::RIGHT, 10)
            << std::endl;

  return 0;
}
