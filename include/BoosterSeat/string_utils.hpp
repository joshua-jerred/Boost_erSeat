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

/**
 * @brief Checks if a string contains a prefix
 *
 * @param str - The string to check
 * @param prefix - The prefix to check for
 * @return true - If the string contains the prefix
 * @return false - If the string does not contain the prefix
 */
inline bool containsPrefix(const std::string &str, const std::string &prefix) {
  return str.find(prefix) == 0;
}

/**
 * @brief Checks if a string contains a suffix
 *
 * @param str - The string to check
 * @param suffix - The suffix to check for
 * @return true - If the string contains the suffix
 * @return false - If the string does not contain the suffix
 */
inline bool containsSuffix(const std::string &str, const std::string &suffix) {
  return str.rfind(suffix) == str.size() - suffix.size();
}

} // namespace BoosterSeat

#endif /* STRING_UTILS_HPP_ */