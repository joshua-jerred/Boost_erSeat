#ifndef RANDOM_HPP_
#define RANDOM_HPP_

#include <random>

namespace bst {

/**
 * @brief Generates a random hex string of the given length.
 * @param length - The length of the string to generate.
 * @return std::string - The generated string.
 */
std::string randomHexString(unsigned int length);

} // namespace bst

#endif // RANDOM_HPP_