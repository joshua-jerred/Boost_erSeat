#ifndef SLEEP_HPP_
#define SLEEP_HPP_

#include <thread>

namespace BoosterSeat {

/**
 * @brief A blocking sleep function.
 * @param milliseconds
 */
inline void threadSleep(double milliseconds) {
  std::this_thread::sleep_for(
      std::chrono::milliseconds(static_cast<int>(milliseconds)));
}

} // namespace BoosterSeat

#endif