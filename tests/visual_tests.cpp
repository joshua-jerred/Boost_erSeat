// just a simple visual test

#include <BoosterSeat/random.hpp>
#include <BoosterSeat/sleep.hpp>
#include <BoosterSeat/string_formatting.hpp>
#include <BoosterSeat/time.hpp>
#include <BoosterSeat/timer.hpp>
#include <iostream>

int main() {
  // Without delimiter argument
  std::cout << "without delimiter argument" << std::endl;
  std::cout << "timeString UTC   | "
            << bst::time::timeString(bst::time::TimeZone::UTC) << std::endl;
  std::cout << "timeString Local | " << bst::time::timeString() << std::endl;
  std::cout << "dateString Local | " << bst::time::dateString() << std::endl;
  std::cout << std::endl;

  // With delimiter argument
  std::cout << "with delimiter argument" << std::endl;
  std::cout << "timeString UTC   | "
            << bst::time::timeString(bst::time::TimeZone::UTC, '/')
            << std::endl;
  std::cout << "timeString Local | "
            << bst::time::timeString(bst::time::TimeZone::LOCAL, '/')
            << std::endl;
  std::cout << "dateString Local | "
            << bst::time::dateString(bst::time::TimeZone::LOCAL, '/')
            << std::endl;
  std::cout << std::endl;

  // With delimiter argument
  std::cout << "with null delimiter argument" << std::endl;
  std::cout << "timeString UTC   | "
            << bst::time::timeString(bst::time::TimeZone::UTC, '\0')
            << std::endl;
  std::cout << "timeString Local | "
            << bst::time::timeString(bst::time::TimeZone::LOCAL, '\0')
            << std::endl;
  std::cout << "dateString Local | "
            << bst::time::dateString(bst::time::TimeZone::LOCAL, '\0')
            << std::endl;
  std::cout << std::endl;

  // getDateAndTimeStr
  std::cout << "getDateAndTimeStr | " << bst::time::dateAndTimeString()
            << std::endl;
  std::cout << "getDateAndTimeStr | "
            << bst::time::dateAndTimeString(bst::time::TimeZone::UTC, '*', '$',
                                            '#')
            << std::endl;
  std::cout << std::endl;

  // elapsedAsciiClock
  std::cout << "elapsedAsciiClock" << std::endl;
  auto time_point = bst::clck::now();
  std::cout << "elapsedAsciiClock | "
            << bst::time::elapsedAsciiClock(time_point) << std::endl;
  bst::sleep(1000);
  std::cout << "elapsedAsciiClock | "
            << bst::time::elapsedAsciiClock(time_point) << std::endl;

  std::cout << std::endl;

  // dateAndTimeToTimePoint
  std::cout << "dateAndTimeToTimePoint | ";
  auto tp = bst::time::dateAndTimeToTimePoint(2021, 2, 3, 4, 5, 6);
  std::cout << bst::time::dateAndTimeString(bst::time::TimeZone::LOCAL, '-',
                                            ' ', ':', tp)
            << std::endl;

  std::cout << std::endl;

  // random hex string
  std::cout << "random hex string | " << bst::randomHexString(10) << std::endl;

  bst::Timer timer(50);
  std::cout << "timer started" << std::endl;
  while (!timer.isDone()) {
    std::cout << "timer not done" << std::endl;
    bst::sleep(20);
  }
  std::cout << "timer done" << std::endl;
  timer.reset();
  while (!timer.isDone()) {
    std::cout << "timer not done" << std::endl;
    bst::sleep(20);
  }

  std::vector<std::vector<std::string>> out = {{"hello", "world", "this"},
                                               {"is", "a", "test"},
                                               {"of", "the", "emergency"},
                                               {"broadcast", "system", "!"}};

  bst::layout::Alignment align = bst::layout::Alignment::LEFT;
  int column_width = 15;

  std::cout << bst::layout::simpleColumns(out, align, column_width);

  std::cout << std::endl;

  std::vector<std::string> row = {"hello", "there", "world"};
  align = bst::layout::Alignment::CENTER;
  int row_width = 30;

  std::cout << bst::layout::fixedWidthRow(row, align, row_width) << std::endl;
  std::cout << bst::layout::fixedWidthString("hello",
                                             bst::layout::Alignment::RIGHT, 10)
            << std::endl;

  return 0;
}
