#include <BoosterSeat/rolling_average.hpp>

namespace bst {

RollingAverage::RollingAverage(size_t window_size) : window_size_(window_size) {
}

void RollingAverage::addValue(double value) {
  queue_.push(value);
  sum_ += value;

  if (queue_.size() > window_size_) {
    sum_ -= queue_.front(); // remove the oldest transaction count from the sum
    queue_.pop();           // and the queue
  }
}

double RollingAverage::getAverage() const {
  double size = static_cast<double>(queue_.size());
  if (size < 1) { // avoid divide by zero and float comparison
    return 0.0;
  }
  return sum_ / size;
}

void RollingAverage::setWindowSize(size_t new_window_size) {
  window_size_ = new_window_size;
  while (queue_.size() > window_size_) {
    sum_ -= queue_.front();
    queue_.pop();
  }
}

} // namespace bst