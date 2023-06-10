#include <BoosterSeat/exception.hpp>
#include <BoosterSeat/filesystem.hpp>
#include <BoosterSeat/numbers.hpp>

#include "gtest/gtest.h"
#include <filesystem>
#include <fstream>
#include <sstream>

/**
 * @details Manually need to create files/directories for "NO_PERM_CHECKS".
 *
 * In the same directory as the executable, create the following with
 * no read/write permissions for the user:
 * ./perm_test_dir
 * ./perm_test_dir/perm_test_file.txt
 *
 */
#define NO_PERM_CHECKS

namespace bsfs = BoosterSeat::filesystem;
using namespace BoosterSeat;

inline void createFileOfSizeMb(const std::string file_path,
                               const int file_size_mb) {
  std::ofstream file(file_path, std::ios::binary | std::ios::out);
  ASSERT_TRUE((bool)file) << "Failed to create file to set up test.";
  for (int i = 0; i < file_size_mb * 1024 * 1024; ++i) {
    file << "0";
  }
}

TEST(FileSystemTests, doesFileExist) {
  // Test that a file that does not exist returns false.
  EXPECT_FALSE(bsfs::doesFileExist("nonexistent_file.txt"));

  // Test that a file that does exist returns true.
  const std::string file_name = "test_file.txt";
  std::ofstream file(file_name);
  ASSERT_TRUE(file.is_open()) << "Failed to create file to set up test.";
  file.close();
  EXPECT_TRUE(bsfs::doesFileExist(file_name));

  // Create a directory to test that a directory doesFileExist raises an
  // exception.
  const std::string dir_name = "test_dir";
  std::filesystem::create_directory(dir_name);

  try {
    bsfs::doesFileExist(dir_name);
    FAIL() << "Expected doesFileExist to throw an exception.";
  } catch (const BoosterSeatException &e) {
    EXPECT_EQ(e.errorNumberEnum(), ErrorNumber::FS_PATH_NOT_REGULAR_FILE);
  }
}

TEST(FileSystemTests, createFile) {
  // Setup the test by removing test_file.txt if it exists.
  const std::string file_name = "test_file.txt";
  if (std::filesystem::exists(file_name)) {
    std::filesystem::remove(file_name);
  }

  // Test that a file that does not exist is created.
  bsfs::createFile(file_name);
  EXPECT_TRUE(bsfs::doesFileExist(file_name));

  // Test that a file that does exist raises an exception.
  try {
    bsfs::createFile(file_name);
    FAIL() << "Expected createFile to throw an exception.";
  } catch (const BoosterSeatException &e) {
    EXPECT_EQ(e.errorNumberEnum(), ErrorNumber::FS_PATH_ALREADY_EXISTS);
  }
}

TEST(FileSystemTests, appendToFile) {
  // Setup the test by creating a file with some text.
  const std::string file_name = "test_file.txt";
  const std::string text = "This is some text.";
  std::ofstream file(file_name);
  ASSERT_TRUE(file.is_open()) << "Failed to create file to set up test.";
  file << text;
  file.close();

  // Test that the text is appended to the file, and that a newline is added.
  const std::string text_to_append = "This is some more text.";

  bsfs::appendToFile(file_name, text_to_append);

  std::ifstream file2(file_name);
  ASSERT_TRUE(file2.is_open()) << "Failed to open file to test.";
  std::stringstream file_contents;
  file_contents << file2.rdbuf();
  EXPECT_EQ(file_contents.str(), text + text_to_append + "\n");

  // Redo without a newline.
  std::ofstream file3(file_name);
  ASSERT_TRUE(file3.is_open()) << "Failed to create file to set up test.";
  file3 << text;
  file3.close();

  bsfs::appendToFile(file_name, text_to_append, false); // No newline.

  std::ifstream file4(file_name);
  ASSERT_TRUE(file4.is_open()) << "Failed to open file to test.";
  std::stringstream file_contents2;
  file_contents2 << file4.rdbuf();
  EXPECT_EQ(file_contents2.str(), text + text_to_append);

  // Test for exception if file does not exist.
  try {
    bsfs::appendToFile("nonexistent_file.txt", text_to_append);
    FAIL() << "Expected appendToFile to throw an exception.";
  } catch (const BoosterSeatException &e) {
    EXPECT_EQ(e.errorNumberEnum(), ErrorNumber::FS_PATH_DOES_NOT_EXIST);
  }
}

TEST(FileSystemTests, overwriteFile) {
  // Setup the test by creating a file with some text.
  const std::string file_name = "test_file.txt";
  const std::string text = "This is some text.";
  std::ofstream file(file_name);
  ASSERT_TRUE(file.is_open()) << "Failed to create file to set up test.";
  file << text;
  file.close();

  // Test that the file is overwritten.
  const std::string text_to_overwrite = "This is some more text.";

  bsfs::overwriteFile(file_name, text_to_overwrite);

  std::ifstream file2(file_name);
  ASSERT_TRUE(file2.is_open()) << "Failed to open file to test.";
  std::stringstream file_contents;
  file_contents << file2.rdbuf();
  EXPECT_EQ(file_contents.str(), text_to_overwrite);

  // Test for exception if file does not exist.
  try {
    bsfs::overwriteFile("nonexistent_file.txt", text_to_overwrite);
    FAIL() << "Expected overwriteFile to throw an exception.";
  } catch (const BoosterSeatException &e) {
    EXPECT_EQ(e.errorNumberEnum(), ErrorNumber::FS_PATH_DOES_NOT_EXIST);
  }
}

inline void validateSize(const double size, const double expected_size) {
  constexpr double tolerance = 0.001; // 0.1% tolerance.
  EXPECT_TRUE(isApproxEqualPercent(size, expected_size, tolerance))
      << "Size: " << size << " Expected size: " << expected_size;
}

TEST(FileSystemTests, getFileSize) {
  //// Setup
  // Create a file of known size.
  constexpr int file_size_mb = 4;
  const std::string file_name = "test_file.txt";
  createFileOfSizeMb(file_name, file_size_mb);

  //// Test
  constexpr double expected_bits = file_size_mb * 1024.0 * 1024.0 * 8.0;
  constexpr double expected_bytes = file_size_mb * 1024.0 * 1024.0;
  constexpr double expected_kilobytes = file_size_mb * 1024.0;
  constexpr double expected_megabytes = file_size_mb;
  constexpr double expected_gigabytes = file_size_mb / 1024.0;
  constexpr double expected_terabytes = file_size_mb / 1024.0 / 1024.0;

  validateSize(bsfs::getFileSize(file_name, bsfs::units::Size::BITS),
               expected_bits);
  validateSize(bsfs::getFileSize(file_name),
               expected_bytes); // Default is bytes.
  validateSize(bsfs::getFileSize(file_name, bsfs::units::Size::BYTES),
               expected_bytes);
  validateSize(bsfs::getFileSize(file_name, bsfs::units::Size::KILOBYTES),
               expected_kilobytes);
  validateSize(bsfs::getFileSize(file_name, bsfs::units::Size::MEGABYTES),
               expected_megabytes);
  validateSize(bsfs::getFileSize(file_name, bsfs::units::Size::GIGABYTES),
               expected_gigabytes);
  validateSize(bsfs::getFileSize(file_name, bsfs::units::Size::TERABYTES),
               expected_terabytes);
}

TEST(FileSystemTests, deleteFile) {
  // Setup the test by creating a file.
  const std::string file_name = "test_file.txt";
  std::ofstream file(file_name);
  ASSERT_TRUE(file.is_open()) << "Failed to create file to set up test.";
  file.close();

  EXPECT_TRUE(bsfs::doesFileExist(file_name));
  // Test that the file is deleted.
  bsfs::deleteFile(file_name);

  EXPECT_FALSE(bsfs::doesFileExist(file_name));

  // Test that a file that does not exist raises an exception.
  try {
    bsfs::deleteFile(file_name);
    FAIL() << "Expected deleteFile to throw an exception.";
  } catch (const BoosterSeatException &e) {
    EXPECT_EQ(e.errorNumberEnum(), ErrorNumber::FS_PATH_DOES_NOT_EXIST);
  }
}

TEST(FileSystemTests, doesDirectoryExist_createDirectory) {
  // Setup the test by creating a directory.
  const std::string directory_name = "test_directory";

  if (std::filesystem::exists(directory_name)) {
    std::filesystem::remove_all(directory_name);
  }

  bsfs::createDirectory(directory_name);

  // Test that the directory exists.
  EXPECT_TRUE(bsfs::doesDirectoryExist(directory_name));

  // Test that a directory that does not exist returns false.
  EXPECT_FALSE(bsfs::doesDirectoryExist("nonexistent_directory"));

  // Test that a file that does not exist returns false.
  EXPECT_FALSE(bsfs::doesDirectoryExist("nonexistent_file.txt"));

  // Test that if it is a file, it raises an exception.
  const std::string file_name = "test_file.txt";
  std::ofstream file(file_name);
  ASSERT_TRUE(file.is_open()) << "Failed to create file to set up test.";
  file.close();
  ASSERT_TRUE(bsfs::doesFileExist(file_name));
  try {
    bsfs::doesDirectoryExist(file_name);
    FAIL() << "Expected doesDirectoryExist to throw an exception.";
  } catch (const BoosterSeatException &e) {
    EXPECT_EQ(e.errorNumberEnum(), ErrorNumber::FS_PATH_NOT_DIRECTORY);
  }
}

TEST(FileSystemTests, directorySize) {
  // Setup the test by creating a directory.
  const std::string directory_name = "test_directory_size";
  const std::string subdir = directory_name + "/subdir";

  if (std::filesystem::exists(directory_name)) {
    std::filesystem::remove_all(directory_name);
  }

  bsfs::createDirectory(directory_name);
  createFileOfSizeMb(directory_name + "/test_file1.txt", 1);
  createFileOfSizeMb(directory_name + "/test_file2.txt", 2);
  createFileOfSizeMb(directory_name + "/test_file3.txt", 3);

  // Test that the directory size is correct.
  constexpr double expected_bytes = 6 * 1024.0 * 1024.0;
  validateSize(bsfs::getDirectorySize(directory_name), expected_bytes);

  // Try with a subdirectory.
  bsfs::createDirectory(subdir);
  createFileOfSizeMb(subdir + "/test_file4.txt", 4);
  createFileOfSizeMb(subdir + "/test_file5.txt", 5);

  // Test that the directory size is correct.
  constexpr double expected_bytes_subdir = 15 * 1024.0 * 1024.0;
  validateSize(bsfs::getDirectorySize(directory_name), expected_bytes_subdir);
}

TEST(FileSystemTests, hasWritePermission) {
  // Setup the test by creating a file.
  const std::string file_name = "test_file.txt";
  std::ofstream file(file_name);
  ASSERT_TRUE(file.is_open()) << "Failed to create file to set up test.";
  file.close();

  // Test that the file has write permission.
  EXPECT_TRUE(bsfs::hasWritePermission(file_name));
}

TEST(FileSystemTests, hasReadPermission) {
  // Setup the test by creating a file.
  const std::string file_name = "test_file.txt";
  std::ofstream file(file_name);
  ASSERT_TRUE(file.is_open()) << "Failed to create file to set up test.";
  file.close();

  // Test that the file has read permission.
  EXPECT_TRUE(bsfs::hasReadPermission(file_name));
}

#ifdef NO_PERM_CHECKS
TEST(FileSystemTests, NO_PERM_hasWritePermission) {
  // Files already created see `// #define NO_PERM_CHECKS` above.
  EXPECT_FALSE(bsfs::hasWritePermission("perm_test_dir")); // Directory
  EXPECT_FALSE(
      bsfs::hasWritePermission("perm_test_dir/perm_test_file.txt")); // File
}
#endif

TEST(FileSystemTests, moveFileTest) {
  const std::string file_name = "move_test_file.txt";
  const std::string directory_name = "move_test_directory";

  // Clean up from previous test runs.
  if (std::filesystem::exists(file_name)) {
    std::filesystem::remove(file_name);
  }
  if (std::filesystem::exists(directory_name)) {
    std::filesystem::remove_all(directory_name);
  }

  // Create a file to move and a directory to move it to.
  std::ofstream file(file_name);
  ASSERT_TRUE(file.is_open()) << "Failed to create file to set up test.";
  file.close();
  bsfs::createDirectory(directory_name);

  // Move the file.
  const std::string new_file_name = directory_name + "/move_test_file.txt";
  bsfs::moveFile(file_name, new_file_name);

  // Test that the file was moved.
  EXPECT_FALSE(bsfs::doesFileExist(file_name));
  EXPECT_TRUE(bsfs::doesFileExist(new_file_name));
}

TEST(FileSystemTests, getFileName) {
  std::string file_name = "test.file";
  std::string dir = "nested/test/dir/";
  std::string full_path = dir + file_name;

  EXPECT_EQ(bsfs::getFileName(full_path), file_name);
}