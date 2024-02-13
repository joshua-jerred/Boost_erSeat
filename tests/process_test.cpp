#include <BoosterSeat/process.hpp>

#include <iostream>
#include <sstream>

#include "gtest/gtest.h"

inline std::string getOutput(bst::Process &p) {
  std::ostringstream oss;
  oss << "[EXIT CODE]: " << p.getExitCode() << std::endl;
  oss << "[STDOUT]: " << std::endl << p.getStdout() << std::endl;
  oss << "[STDERR]: " << std::endl << p.getStderr() << std::endl;
  oss << std::endl;

  return oss.str();
}

TEST(ProcessTest, basic_output) {
  bst::Process p("ls", {});
  p.waitToComplete();

  ASSERT_EQ(p.getExitCode(), 0) << getOutput(p);
  ASSERT_GT(p.getStdout().size(), 0) << getOutput(p);
  ASSERT_EQ(p.getStderr().size(), 0) << getOutput(p);
}

TEST(ProcessTest, basic_exit_code) {
  bst::Process p("bash", {"-c", "exit 23"});
  p.waitToComplete();

  ASSERT_EQ(p.getExitCode(), 23) << getOutput(p);
  ASSERT_EQ(p.getStdout().size(), 0) << getOutput(p);
  ASSERT_EQ(p.getStderr().size(), 0) << getOutput(p);
}

TEST(ProcessTest, basic_error) {
  bst::Process p("ls", {"/nonexistent"});
  p.waitToComplete();

  ASSERT_NE(p.getExitCode(), 0) << getOutput(p);
  ASSERT_EQ(p.getStdout().size(), 0) << getOutput(p);
  ASSERT_GT(p.getStderr().size(), 0) << getOutput(p);
}

TEST(ProcessTest, basic_input) {
  bst::Process p("cat", {});
  p.writeToInStream("hello\n");
  p.closeInStream();
  p.waitToComplete();

  ASSERT_EQ(p.getExitCode(), 0) << getOutput(p);
  ASSERT_EQ(p.getStdout(), "hello\n") << getOutput(p);
  ASSERT_EQ(p.getStderr().size(), 0) << getOutput(p);
}

TEST(ProcessTest, command_timeout) {
  bst::Process p("sleep", {"2"});

  try {
    p.waitToComplete(1);
    FAIL() << "Expected bst::BoosterSeatException";
  } catch (const bst::BoosterSeatException &e) {
    ASSERT_EQ(e.errorNumberEnum(), bst::ErrorNumber::PROCESS_TIMEOUT);
  }
}