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

} // namespace layout

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
} // namespace string

/**
 * @brief Converts an integer to a hexadecimal string
 *
 * @param i - The integer to convert
 * @param width - The width of the hex string (default: 2)
 * @param include_0x - Whether or not to include the 0x prefix (default: true)
 * @param uppercase - Whether or not to use uppercase letters (default: true)
 * @return std::string
 */
std::string intToHex(const int i, const int width = 2,
                     const bool include_0x = true, const bool uppercase = true);

} // namespace BoosterSeat

#endif