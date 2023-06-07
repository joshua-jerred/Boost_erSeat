#include "BoosterSeat/filesystem.hpp"
#include "BoosterSeat/exception.hpp"

#include <cstdint>
#include <filesystem>
#include <fstream>
#include <type_traits>

// This BoosterSeat Module was made for linux systems only.
#ifdef __linux__
#include <unistd.h>
#else
static_assert(false, "Unsupported platform.");
#endif

namespace bs = BoosterSeat;
namespace fs = bs::filesystem;
typedef bs::ErrorNumber ErrNum;
typedef std::filesystem::path Path;
typedef std::filesystem::recursive_directory_iterator RecursiveDirIter;

/**
 * @brief Internal inline functions used only in this file.
 */
namespace internal {
inline bool exists(const Path &path) {
  return std::filesystem::exists(path);
}

/**
 * @brief Checks if a path is a regular file.
 *
 * @param path - The path to check.
 * @return true - The path is a regular file.
 * @return false - The path is not a regular file.
 */
inline bool is_file(const Path &path) {
  return std::filesystem::is_regular_file(path);
}

/**
 * @brief Returns true if the path is a directory.
 *
 * @param path - The path to check.
 * @return true - The path is a directory.
 * @return false - The path is not a directory.
 */
inline bool is_directory(const Path &path) {
  return std::filesystem::is_directory(path);
}

/**
 * @brief Returns true if the path if the program has write permissions.
 *
 * @param path - The path to check.
 * @return true - The program has write permissions.
 * @return false - The program does not have write permissions.
 */
inline bool has_write_permission(const Path &path) {
  return access(path.string().c_str(), W_OK) == 0;
}

/**
 * @brief Returns true if the program has read permissions.
 *
 * @param path - The path to check.
 * @return true - The program has read permissions.
 * @return false - The program does not have read permissions.
 */
inline bool has_read_permissions(const Path &path) {
  return access(path.string().c_str(), R_OK) == 0;
}

inline std::uintmax_t get_file_size_bytes(const Path &path) {
  return std::filesystem::file_size(path);
}

inline double convertMbToUnit(const double size_mb,
                              const fs::units::Size unit) {
  switch (unit) {
  case fs::units::Size::BITS:
    return size_mb * 8;
  case fs::units::Size::BYTES:
    return size_mb;
  case fs::units::Size::KILOBYTES:
    return size_mb / 1024;
  case fs::units::Size::MEGABYTES:
    return size_mb / 1024 / 1024;
  case fs::units::Size::GIGABYTES:
    return size_mb / 1024 / 1024 / 1024;
  case fs::units::Size::TERABYTES:
    return size_mb / 1024 / 1024 / 1024 / 1024;
  default:
    throw bs::BoosterSeatException("Invalid size unit.",
                                   ErrNum::FS_INVALID_SIZE_UNIT);
  }
}
}; // namespace internal

namespace assertions {
/**
 * @brief Checks if a path exists, otherwise it will throw an exception.
 * @param path - The path to check.
 * @exception BoosterSeatException - If the path does not exist.
 */
inline void Exists(const Path &path) {
  if (!internal::exists(path)) {
    throw bs::BoosterSeatException(path.string(),
                                   ErrNum::FS_PATH_DOES_NOT_EXIST);
  }
}

/**
 * @brief Checks if a path exists, otherwise it will throw an exception.
 * @param path - The path to check.
 * @exception BoosterSeatException - If the path does exist.
 */
inline void DoesNotExist(const Path &path) {
  if (internal::exists(path)) {
    throw bs::BoosterSeatException(path.string(),
                                   ErrNum::FS_PATH_ALREADY_EXISTS);
  }
}

/**
 * @brief Checks if the path exists and is a regular file, otherwise it will
 * throw an exception.
 * @param path - The path to check.
 * @exception BoosterSeatException - If the path does not exist or is not a
 */
inline void IsRegularFile(const Path &path) {
  assertions::Exists(path);
  if (!std::filesystem::is_regular_file(path)) {
    throw bs::BoosterSeatException(path.string(),
                                   ErrNum::FS_PATH_NOT_REGULAR_FILE);
  }
}

/**
 * @brief Checks if the path exists and is a directory, otherwise it will throw
 * an exception.
 * @param path - The path to check.
 * @exception BoosterSeatException - If the path does not exist or is not a
 */
inline void IsDirectory(const Path &path) {
  assertions::Exists(path);
  if (!std::filesystem::is_directory(path)) {
    throw bs::BoosterSeatException(path.string(),
                                   ErrNum::FS_PATH_NOT_DIRECTORY);
  }
}

/**
 * @brief Checks if the file is open and valid, otherwise it will throw an
 * exception with the error code. This function is only for ifstream and
 * ofstream. Used after opening a file.
 * @param path - The path to the file.
 * @param file - The fstream object to check.
 */
template <typename T>
inline void FileValid(const Path &path, T &file) {
  // Template type validation.
  static_assert(std::is_same<T, std::ifstream>::value ||
                    std::is_same<T, std::ofstream>::value,
                "The file must be an ifstream or ofstream.");

  if (!file) { // Checks if open and valid.
    throw bs::BoosterSeatException("Stream errno:" + std::to_string(errno) +
                                       " | " + path.string(),
                                   ErrNum::FS_FILE_NOT_VALID);
  }
}

/**
 * @brief Checks a program has write permissions to the file or directory at the
 * path, if not, throws an exception. Only works on Linux at the moment,
 * requires the <unistd.h> header.
 * @param path - The path to the file.
 * @exception BoosterSeatException - If the file does not have write
 * permissions.
 */
inline void WritePermissions(const Path &path) {

  if (internal::has_write_permission(path)) {
    throw bs::BoosterSeatException(path.string(),
                                   ErrNum::FS_NO_WRITE_PERMISSIONS);
  }
}

/**
 * @brief Only works on Linux at the moment, requires the <unistd.h> header.
 * @param path
 * @exception BoosterSeatException - If the file does not have read permissions.
 */
inline void ReadPermissions(const Path &path) {
  if (internal::has_read_permissions(path)) {
    throw bs::BoosterSeatException(path.string(),
                                   ErrNum::FS_NO_READ_PERMISSIONS);
  }
}

} // namespace assertions

// -- Public functions --------------------------------------------------------
// All documentation is in the header file.

bool fs::doesFileExist(const std::string &file_path) {
  Path path(file_path);
  if (!internal::exists(path)) {
    return false;
  }
  if (!internal::is_file(
          path)) { // The object is not a file (probably a directory).
    throw bs::BoosterSeatException(path.string(),
                                   ErrNum::FS_PATH_NOT_REGULAR_FILE);
  }
  return true;
}

void fs::createFile(const std::string &file_path) {
  Path path(file_path);
  assertions::DoesNotExist(path);    // The file should not exist.
  std::ofstream file(file_path);     // Create the file.
  assertions::FileValid(path, file); // Check the file is valid.
}

void fs::appendToFile(const std::string &file_path, const std::string &data,
                      const bool new_line_after) {
  Path path(file_path);
  assertions::IsRegularFile(path);

  std::ofstream file(file_path, std::ios::app); // Open the file in append mode.

  assertions::FileValid(path, file);
  file << data;         // Write the data to the file.
  if (new_line_after) { // Add a new line if required.
    file << std::endl;
  }
  assertions::FileValid(path, file);
}

void fs::overwriteFile(const std::string &file_path,
                       const std::string &content) {
  Path path(file_path);
  assertions::IsRegularFile(path);

  std::ofstream file(file_path, std::ios::trunc); // Open the file in truncate
                                                  // mode. (Overwrite)

  assertions::FileValid(path, file);
  file << content; // Write the data to the file.
  assertions::FileValid(path, file);
}

double fs::getFileSize(const std::string &file_path,
                       fs::units::Size size_unit) {
  Path path(file_path);
  assertions::IsRegularFile(path);

  double size = internal::get_file_size_bytes(path);

  return internal::convertMbToUnit(size, size_unit);
}

void fs::deleteFile(const std::string &file_path) {
  Path path(file_path);
  assertions::IsRegularFile(path);
  //assertions::WritePermissions(path); // Causing an exception
  std::filesystem::remove(path);
}

bool fs::doesDirectoryExist(const std::string &directory_path) {
  Path path(directory_path);
  if (!internal::exists(path)) {
    return false;
  }
  if (!internal::is_directory(
          path)) { // The object is not a directory (probably a file).
    throw bs::BoosterSeatException(path.string(),
                                   ErrNum::FS_PATH_NOT_DIRECTORY);
  }
  return true;
}

void fs::createDirectory(const std::string &directory_path) {
  Path path(directory_path);
  assertions::DoesNotExist(path); // The directory should not exist.
  std::filesystem::create_directory(path);
}

double fs::getDirectorySize(const std::string &directory_path,
                            fs::units::Size size_unit) {
  Path path(directory_path);
  assertions::IsDirectory(path);

  double size = 0;
  for (const auto &entry :
       std::filesystem::recursive_directory_iterator(path)) {
    // Ignore everything that is not a regular file.
    if (entry.is_regular_file()) {
      size += internal::get_file_size_bytes(entry.path());
    }
  }

  return internal::convertMbToUnit(size, size_unit);
}

bool fs::hasWritePermission(const std::string &object_path) {
  Path path(object_path);
  return internal::has_write_permission(path);
}

bool fs::hasReadPermission(const std::string &object_path) {
  Path path(object_path);
  return internal::has_read_permissions(path);
}