#ifndef STRING_UTILS_HPP_
#define STRING_UTILS_HPP_

#include <string>

namespace BoosterSeat {

/**
 * @brief Checks if a string contains a substring
 *
 * @param str - The string to check
 * @param sub - The substring to check for
 * @return true - If the string contains the substring
 * @return false - If the string does not contain the substring
 */
inline bool containsSubstring(const std::string &str, const std::string &sub) {
  return str.find(sub) != std::string::npos;
}
} // namespace BoosterSeat

#endif /* STRING_UTILS_HPP_ */