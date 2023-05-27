#ifndef EXCEPTION_HPP_
#define EXCEPTION_HPP_

#include <stdexcept>
#include <string>

namespace BoosterSeat {

class BoosterSeatException : public std::exception {
 public:
  BoosterSeatException(const std::string& message) : message_(message) {
  }
  ~BoosterSeatException() = default;

  const char* what() const noexcept override {
    return message_.c_str();
  }

 private:
  std::string message_;
};

}  // namespace BoosterSeat

#endif  // BOOST_ERSEAT_HPP_