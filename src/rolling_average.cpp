#include <Bst/rolling_average.hpp>

using namespace BoosterSeat;

RollingAverage::RollingAverage(int window_size) : window_size_(window_size) {
}

void RollingAverage::count(double count) {
  count_ += count;
}

void RollingAverage::intervalCall() {
  queue_.push(count_);
  sum_ += count_;
  count_ = 0.0;

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