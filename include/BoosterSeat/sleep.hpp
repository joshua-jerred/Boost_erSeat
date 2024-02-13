#ifndef SLEEP_HPP_
#define SLEEP_HPP_

#include <thread>

namespace bst {
inline void sleep(int32_t milliseconds) {
  std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}
} // namespace bst

#endif