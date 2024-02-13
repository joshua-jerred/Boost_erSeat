/**
 * @file process.hpp
 * @author Joshua Jerred (https://joshuajer.red)
 * @brief A class to handle linux process calls
 *
 * @date 2024-02-12
 * @copyright Copyright (c) 2024
 */

#ifndef BOOSTER_SEAT_PROCESS_HPP_
#define BOOSTER_SEAT_PROCESS_HPP_

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include <ext/stdio_filebuf.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include <BoosterSeat/exception.hpp>
#include <BoosterSeat/sleep.hpp>

namespace bst {

/**
 * @brief A class to handle linux process calls.
 * @details This is a rework of the project
 * [cpp-subprocess](https://github.com/tsaarni/cpp-subprocess)
 */
class Process {
public:
  Process(const std::string &cmd, std::vector<std::string> argv);
  ~Process();

  void writeToInStream(const std::string &s);
  void closeInStream();
  const std::string &getStdout();
  const std::string &getStderr();
  int getExitCode();

  /**
   * @brief Waits for the process to complete. If the process does not complete
   * within the timeout, a std::system_error is thrown.
   *
   * @param timeout The number of milliseconds to wait for the process to exit.
   * Default is 1000ms.
   */
  void waitToComplete(unsigned int timeout = 1000);

private:
  void assertComplete();
  void run(const std::string &cmd, std::vector<std::string> argv);
  void child(const std::vector<std::string> &argv);

  /// @brief The process id of the child process
  pid_t pid_;

  /// @brief The file descriptors for input pipe
  int in_pipe_[2];
  /// @brief The file descriptors for output pipe
  int out_pipe_[2];
  /// @brief The file descriptors for error pipe
  int err_pipe_[2];

  /// @brief The filebuf for input pipe
  __gnu_cxx::stdio_filebuf<char> *p_in_filebuf_;
  /// @brief The filebuf for output pipe
  __gnu_cxx::stdio_filebuf<char> *p_out_filebuf_;
  /// @brief The filebuf for error pipe
  __gnu_cxx::stdio_filebuf<char> *p_err_filebuf_;

  /// @brief The input stream for the child process
  std::ostream *in_stream_;
  /// @brief The output stream for the child process
  std::istream *out_stream_;
  /// @brief The error stream for the child process
  std::istream *err_stream_;

  /**
   * @brief Set to true when the process has completed and an exit code has been
   * retrieved. This is used internally to check if the process has completed.
   */
  bool have_exit_code_ = false;

  /// @brief The exit code of the process
  int exit_code_ = 0;
  /// @brief The stdout of the process
  std::string stdout_string_;
  /// @brief The stderr of the process
  std::string stderr_string_;
};

} // namespace bst

#endif /* BOOSTER_SEAT_PROCESS_HPP_ */