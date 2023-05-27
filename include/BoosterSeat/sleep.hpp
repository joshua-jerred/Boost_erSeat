#ifndef SLEEP_HPP_
#define SLEEP_HPP_

#include <thread>

namespace BoosterSeat {
namespace util {

/**
 * @brief A blocking sleep function.
 * @param milliseconds
 */
inline void sleep(double milliseconds) {
  std::this_thread::sleep_for(
      std::chrono::milliseconds(static_cast<int>(milliseconds)));
}

}  // namespace util

}  // namespace BoosterSeat

#endif