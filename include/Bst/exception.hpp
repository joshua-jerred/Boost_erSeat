#ifndef EXCEPTION_HPP_
#define EXCEPTION_HPP_

#include <Bst/template_tools.hpp>
#include <stdexcept>
#include <string>

namespace BoosterSeat {

enum class ErrorNumber {
  /**
   * @brief Default value, just for backwards compatibility. Should not be used
   * in new code.
   *
   */
  UNSPECIFIED = 0, // Default value, just for backwards compatibility.

  // -- Filesystem

  /**
   * @brief Path does not exist when it should. Includes path in message.
   */
  FS_PATH_DOES_NOT_EXIST = 1,

  /**
   * @brief Path already exists when it should not. Includes path in message.
   */
  FS_PATH_ALREADY_EXISTS = 2,

  /**
   * @brief Path is not a regular file. Includes path in message.
   */
  FS_PATH_NOT_REGULAR_FILE = 3,

  /**
   * @brief Path is not a directory. Includes path in message.
   */
  FS_PATH_NOT_DIRECTORY = 4,

  /**
   * @brief File is not valid. Includes if/ofstream error code in message.
   * @details Format: "Stream errno:<errorno> | <path>"
   */
  FS_FILE_NOT_VALID = 5,

  /**
   * @brief Throw if write permissions are required but do not exist.
   */
  FS_NO_WRITE_PERMISSIONS = 6,

  /**
   * @brief Throw if read permissions are required but do not exist.
   */
  FS_NO_READ_PERMISSIONS = 7,

  /**
   * @brief Thrown if an invalid size unit is used.
   */
  FS_INVALID_SIZE_UNIT = 8,

  /**
   * @brief Thrown if an invalid time zone is used.
   */
  TIME_INVALID_TIMEZONE = 9,

  /**
   * @brief Latitude is out of range/invalid.
   */
  GEO_INVALID_LATITUDE = 10,

  /**
   * @brief Longitude is out of range/invalid.
   */
  GEO_INVALID_LONGITUDE = 11,

  /**
   * @brief Invalid time.
   */
  TIME_INVALID_TIME = 12,

  /**
   * @brief Throws if a feature is not yet implemented.
   */
  NOT_YET_IMPLEMENTED
};

class BoosterSeatException : public std::exception {
public:
  BoosterSeatException(const std::string &message,
                       ErrorNumber error_number = ErrorNumber::UNSPECIFIED)
      : error_number_enum_(error_number),
        error_number_(template_tools::to_underlying(error_number)),
        message_("BS Errno: " + std::to_string(error_number_) + " |" +
                 message) {
  }
  ~BoosterSeatException() = default;

  const char *what() const noexcept override {
    return message_.c_str();
  }

  ErrorNumber errorNumberEnum() const noexcept {
    return error_number_enum_;
  }

  int errorNumber() const noexcept {
    return error_number_;
  }

private:
  ErrorNumber error_number_enum_;
  int error_number_;
  std::string message_;
};

} // namespace BoosterSeat

#endif // BOOST_ERSEAT_HPP_