// just a simple visual test

#include <BoosterSeat/string_formatting.hpp>
#include <BoosterSeat/time.hpp>
#include <iostream>
#include <string>
#include <vector>

int main() {
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

  std::cout << BoosterSeat::layout::fixedWidthRow(row, align, row_width) << std::endl;
  std::cout << BoosterSeat::layout::fixedWidthString("hello", BoosterSeat::layout::Alignment::RIGHT, 10) << std::endl;

  std::cout << BoosterSeat::time::getDateAndTimeStr() << std::endl;
  return 0;
}
