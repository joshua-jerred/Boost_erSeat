#ifndef RANDOM_HPP_
#define RANDOM_HPP_

#include <random>

namespace BoosterSeat {

/**
 * @brief Generates a random hex string of the given length.
 * @param length - The length of the string to generate.
 * @return std::string - The generated string.
 */
std::string randomHexString(unsigned int length);

} // namespace BoosterSeat

#endif // RANDOM_HPP_