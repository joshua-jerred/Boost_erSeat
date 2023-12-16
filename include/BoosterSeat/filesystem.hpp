#ifndef FILESYSTEM_HPP_
#define FILESYSTEM_HPP_

#include <string>

namespace BoosterSeat {
namespace filesystem {
namespace units {
enum class Size { BITS, BYTES, KILOBYTES, MEGABYTES, GIGABYTES, TERABYTES };

enum class Type { FILE, DIRECTORY };
} // namespace units

/**
 * @brief Returns a boolean indicating whether or not the file exists. If it's
 * a directory an exception will be thrown.
 *
 * @param file_path The path to the file.
 * @return true - The file exists, false otherwise.
 *
 * @exception BoosterSeatException - If the path is a directory.
 * error.
 */
bool doesFileExist(const std::string &file_path);

/**
 * @brief Create a File.
 * @param file_path The path to the file.
 *
 * @exception BoosterSeatException - If the file already exists or cannot be
 * created.
 */
void createFile(const std::string &file_path);

/**
 * @brief Append a string to a file.
 *
 * @param file_path - The path to the file.
 * @param content - A string to append to the file.
 * @param new_line_after - default true - If true, a new line will be added
 * after the data.
 *
 * @exception BoosterSeatException - If the file already exists, the program
 * does not have write permissions, or the file cannot be opened.
 */
void appendToFile(const std::string &file_path, const std::string &content,
                  const bool new_line_after = true);

/**
 * @brief Overwrite a files with a string.
 *
 * @param file_path - The path to the file.
 * @param content - A string to overwrite the file with.
 *
 * @exception BoosterSeatException - If the file already exists, the program
 * does not have write permissions, or the file cannot be opened.
 */
void overwriteFile(const std::string &file_path, const std::string &content);

/**
 * @brief Get the size of a file.
 *
 * @param file_path - The path to the file
 * @param unit - The unit to return the size in. (default: bytes)
 * @return double - The size of the file in the specified unit.
 *
 * @exception BoosterSeatException - If the path is not a regular file,
 * the size cannot be determined, or the file does not exist.
 */
double getFileSize(const std::string &file_path,
                   units::Size size_unit = units::Size::BYTES);

/**
 * @brief Delete a file.
 * @param file_path - The path to the file.
 * @exception BoosterSeatException - If the file does not exist, the program
 * does not have write permissions, or the file cannot be deleted.
 */
void deleteFile(const std::string &file_path);

/**
 * @brief Returns a boolean indicating whether or not the directory exists.
 *
 * @param directory_path - The path to the directory.
 * @return true - The directory exists.
 * @return false - The directory does not exist in the path.
 * @exception BoosterSeatException - If the path is a file, or the program
 * does not have permissions to read the size of the directory.
 */
bool doesDirectoryExist(const std::string &directory_path);

/**
 * @brief Create a Directory at the specified path.
 *
 * @param directory_path - The path to the directory, including the directory
 * name. (e.g. /home/user/MyNewDirectory)
 *
 * @exception BoosterSeatException - If the directory already exists, the
 * program does not have write permissions, or the directory cannot be created.
 */
void createDirectory(const std::string &directory_path);

/**
 * @brief Get the size of a directory. Only includes regular files.
 *
 * @param directory_path - The path to the directory
 * @param unit - The unit to return the size in. (default: bytes)
 * @param recursive - If true, the size of all subdirectories will be included.
 * @return double - The size of the directory in the specified unit.
 *
 * @exception BoosterSeatException - If the path is not a directory, the size
 * cannot be determined, or the directory does not exist.
 */
double getDirectorySize(const std::string &directory_path,
                        units::Size unit = units::Size::BYTES);

/**
 * @note Only works on Linux systems, currently does not throw an exception
 * if the path does not exist.
 *
 * @brief If a program has write permissions to a file or directory, it will
 * return true. Otherwise, it will return false.
 *
 * @param path - The path to the file or directory.
 * @return true - The program has write permissions.
 * @return false - The program does not have write permissions.
 */
bool hasWritePermission(const std::string &path);

/**
 * @note Only works on Linux systems, currently does not throw an exception
 * if the path does not exist.
 *
 * @brief If a program has read permissions to a file or directory, it will
 * return true. Otherwise, it will return false.
 *
 * @param path - The path to the file or directory.
 * @return true - The program has read permissions.
 * @return false - The program does not have read permissions.
 */
bool hasReadPermission(const std::string &path);

/**
 * @brief Move a file from one location to another.
 *
 * @param source_path - The path to the file to move.
 * @param destination_path - The path to move the file to.
 */
void moveFile(const std::string &source_path,
              const std::string &destination_path, bool overwrite = false);

/**
 * @brief Get the File Name from a path. Does not need to exist.
 *
 * @param file_path - The path to the file.
 * @return std::string - The file name.
 */
std::string getFileName(const std::string &file_path);

} // namespace filesystem
} // namespace BoosterSeat

#endif