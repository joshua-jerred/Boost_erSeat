/**
 * @file process.cpp
 * @author Joshua Jerred (https://joshuajer.red)
 * @brief Process class implementation
 * @date 2024-02-13
 * @copyright Copyright (c) 2024
 */

#include <BoosterSeat/process.hpp>

namespace bst {

Process::Process(const std::string &cmd, std::vector<std::string> argv)
    : p_in_filebuf_(nullptr), p_out_filebuf_(nullptr), p_err_filebuf_(nullptr),
      in_stream_(nullptr), out_stream_(nullptr), err_stream_(nullptr) {
  if (pipe(in_pipe_) == -1 || pipe(out_pipe_) == -1 || pipe(err_pipe_) == -1) {
    throw std::system_error(errno, std::system_category());
  }

  run(cmd, argv);
}

Process::~Process() {
  delete p_in_filebuf_;
  delete in_stream_;
  if (p_out_filebuf_ != nullptr)
    delete p_out_filebuf_;
  if (out_stream_ != nullptr)
    delete out_stream_;
  delete p_err_filebuf_;
  delete err_stream_;
}

void Process::writeToInStream(const std::string &s) {
  in_stream_->write(s.c_str(), s.size());
}

void Process::closeInStream() {
  p_in_filebuf_->close();
}

const std::string &Process::getStdout() {
  assertComplete();
  return stdout_string_;
}

const std::string &Process::getStderr() {
  assertComplete();
  return stderr_string_;
}

int Process::getExitCode() {
  assertComplete();
  return exit_code_;
}

/**
 * @brief Waits for the process to complete. If the process does not complete
 * within the timeout, a std::system_error is thrown.
 *
 * @param timeout The number of milliseconds to wait for the process to exit.
 * Default is 1000ms.
 */
void Process::waitToComplete(unsigned int timeout) {
  int status = 0;

  while (timeout > 0 && waitpid(pid_, &status, WNOHANG) == 0) {
    bst::sleep(1);
    timeout--;
  }

  if (timeout == 0) {
    throw BoosterSeatException("process timed out",
                               ErrorNumber::PROCESS_TIMEOUT);
  }

  exit_code_ = WEXITSTATUS(status);
  have_exit_code_ = true;

  if (out_stream_ == nullptr)
    throw std::system_error(EBADF, std::system_category());

  std::stringstream ss;
  ss << out_stream_->rdbuf();
  stdout_string_ = ss.str();

  if (err_stream_ == nullptr)
    throw std::system_error(EBADF, std::system_category());

  std::stringstream ss2;
  ss2 << err_stream_->rdbuf();
  stderr_string_ = ss2.str();
};

void Process::assertComplete() {
  if (!have_exit_code_) {
    throw bst::BoosterSeatException(
        "out of order function call, process not complete",
        bst::ErrorNumber::PROCESS_NOT_COMPLETE);
  }
}

inline constexpr int K_PIPE_READ = 0;
inline constexpr int K_PIPE_WRITE = 1;

void Process::run(const std::string &cmd, std::vector<std::string> argv) {
  argv.insert(argv.begin(), cmd);

  pid_ = ::fork();

  if (pid_ == 0) {
    child(argv);
  }

  ::close(in_pipe_[K_PIPE_READ]);
  ::close(out_pipe_[K_PIPE_WRITE]);
  ::close(err_pipe_[K_PIPE_WRITE]);

  p_in_filebuf_ = new __gnu_cxx::stdio_filebuf<char>(in_pipe_[K_PIPE_WRITE],
                                                     std::ios_base::out, 1);
  in_stream_ = new std::ostream(p_in_filebuf_);

  if (out_pipe_[K_PIPE_READ] != -1) {
    p_out_filebuf_ = new __gnu_cxx::stdio_filebuf<char>(out_pipe_[K_PIPE_READ],
                                                        std::ios_base::in, 1);
    out_stream_ = new std::istream(p_out_filebuf_);
  }

  p_err_filebuf_ = new __gnu_cxx::stdio_filebuf<char>(err_pipe_[K_PIPE_READ],
                                                      std::ios_base::in, 1);
  err_stream_ = new std::istream(p_err_filebuf_);
}

struct raii_char_str {
  raii_char_str(std::string s) : buf(s.c_str(), s.c_str() + s.size() + 1){};
  operator char *() const {
    return &buf[0];
  };
  mutable std::vector<char> buf;
};

void Process::child(const std::vector<std::string> &argv) {
  if (dup2(in_pipe_[K_PIPE_READ], STDIN_FILENO) == -1 ||
      dup2(out_pipe_[K_PIPE_WRITE], STDOUT_FILENO) == -1 ||
      dup2(err_pipe_[K_PIPE_WRITE], STDERR_FILENO) == -1) {
    std::perror("bst_process: dup2() failed");
    ::exit(-1);
    return;
  }

  ::close(in_pipe_[K_PIPE_READ]);
  ::close(in_pipe_[K_PIPE_WRITE]);
  if (out_pipe_[K_PIPE_READ] != -1)
    ::close(out_pipe_[K_PIPE_READ]);
  ::close(out_pipe_[K_PIPE_WRITE]);
  ::close(err_pipe_[K_PIPE_READ]);
  ::close(err_pipe_[K_PIPE_WRITE]);

  std::vector<raii_char_str> real_args(argv.begin(), argv.end());
  std::vector<char *> cargs(real_args.begin(), real_args.end());
  cargs.push_back(nullptr);

  if (execvp(cargs[0], &cargs[0]) == -1) {
    std::perror("bst_process: execvp() failed");
    ::exit(errno);
  }
}

} // namespace bst