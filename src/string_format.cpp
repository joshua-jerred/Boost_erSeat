#include <BoosterSeat/exception.hpp>
#include <BoosterSeat/string_formatting.hpp>
#include <iomanip>
#include <sstream>

inline void align_cases(std::stringstream &ss,
                        const bst::layout::Alignment align) {
  switch (align) {
  case bst::layout::Alignment::LEFT:
    ss << std::left;
    break;
  case bst::layout::Alignment::RIGHT:
    ss << std::right;
    break;
  case bst::layout::Alignment::CENTER:
    ss << std::internal;
    break;
  }
}

std::string
bst::layout::simpleColumns(const std::vector<std::vector<std::string>> &rows,
                           const Alignment align, const int column_width) {
#ifndef BOOSTERSEAT_NO_EXCEPTION
  if (column_width < 0) {
    throw BoosterSeatException("column_width must be greater than 0");
  }
#endif

  const int column_size = rows[0].size();
  std::stringstream ss;
  for (unsigned int row = 0; row < rows.size(); ++row) {
    for (int col = 0; col < column_size; ++col) {
      ss << std::setw(column_width);
      align_cases(ss, align);
      ss << rows[row][col];
    }
    ss << std::endl;
  }

  return ss.str();
}

std::string bst::layout::fixedWidthRow(const std::vector<std::string> &row,
                                       const Alignment align,
                                       const int row_width) {
#ifndef BOOSTERSEAT_NO_EXCEPTION
  if (row_width < 0) {
    throw BoosterSeatException("row_width must be greater than 0");
  }
#endif

  const int col_width = row_width / row.size();
  std::stringstream ss;

  for (unsigned int col = 0; col < row.size(); col++) {
    ss << std::setw(col_width);
    align_cases(ss, align);
    ss << row[col];
  }

  return ss.str();
}

std::string bst::layout::fixedWidthString(const std::string &s,
                                          const Alignment align,
                                          const int width) {
  std::stringstream ss;
  ss << std::setw(width);
  align_cases(ss, align);
  ss << s;
  return ss.str();
}

std::string bst::string::f2s(const double d, const int precision) {
  std::stringstream ss;
  ss << std::fixed << std::setprecision(precision) << d;
  return ss.str();
}

std::string bst::string::intToHex(const int i, const int width,
                                  const bool include_0x, const bool uppercase) {
  std::stringstream ss;
  ss << std::hex << std::setfill('0');
  if (include_0x) {
    ss << "0x";
  }
  if (uppercase) {
    ss << std::uppercase;
  }
  ss << std::setw(width) << i;
  return ss.str();
}