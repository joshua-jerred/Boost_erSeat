#ifndef STRING_FORMATTING_HPP_
#define STRING_FORMATTING_HPP_

#include <string>
#include <vector>

namespace BoosterSeat {
namespace layout {

enum class Alignment { LEFT, RIGHT, CENTER };

std::string simpleColumns(const std::vector<std::vector<std::string>> &rows,
                          const Alignment align, const int column_width);

std::string fixedWidthRow(const std::vector<std::string> &row,
                          const Alignment align, const int row_width);

std::string fixedWidthString(const std::string &s, const Alignment align,
                            const int width);

}  // namespace format

namespace string {
inline std::string b2s(const bool b, const bool upper = false) {
  if (upper) {
    return b ? "TRUE" : "FALSE";
  } else {
    return b ? "true" : "false";
  }
}

inline std::string i2s(const int i) {
  return std::to_string(i);
}
std::string f2s(const double d, const int precision = 2);
}  // namespace string

}  // namespace BoosterSeat

#endif