#ifndef RANDOM_HPP_
#define RANDOM_HPP_

#include <random>

namespace bst {

/**
 * @brief Generates a random hex string of the given length.
 * @param length - The length of the string to generate.
 * @return std::string - The generated string.
 */
std::string randomHexString(size_t length);

/**
 * @brief Generates a random double within the given range.
 * @param min - The minimum value of the range.
 * @param max - The maximum value of the range.
 * @return double - The generated random double.
 */
double randomDouble(double min, double max);

} // namespace bst

#endif // RANDOM_HPP_