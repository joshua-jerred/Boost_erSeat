# [BST module] Process

The bst process class is a simple interface to run linux commands.

This is a major refactor of the project [cpp-subprocess](https://github.com/tsaarni/cpp-subprocess).

Detailed class documentation can be found [here](@ref bst::Process).

## Example: Basic usage
```cpp
#include <BoosterSeat/process.hpp>
#include <iostream>

int main() {
  bst::Process process("echo", {"Hello, World!"});
  process.waitToComplete();

  std::cout << process.getExitCode() << std::endl;
  std::cout << process.getStdout() << std::endl;
  return 0;
}
```
```sh
$ ./example
0
Hello, World!

```

## Example: Write additional input to stdin
```cpp
#include <BoosterSeat/process.hpp>
#include <iostream>

int main() {
  bst::Process process("cowsay", {});

  process.writeToInStream("hi there\n");
  process.closeInStream();
  
  process.waitToComplete(); // default timeout is 1000ms

  std::cout << process.getExitCode() << std::endl;
  std::cout << process.getStdout() << std::endl;
  std::cout << process.getStderr() << std::endl;
}
```
```sh
$ ./example
0

 __________
< hi there >
 ----------
        \   ^__^
         \  (oo)\_______
            (__)\       )\/\
                ||----w |
                ||     ||
```

## Example: Non-zero command exit codes
```cpp
#include <BoosterSeat/process.hpp>
#include <iostream>

int main() {
  bst::Process process("ls", {"/nonexistent"});
  process.waitToComplete();

  std::cout << process.getExitCode() << std::endl;
  std::cout << process.getStdout() << std::endl;
  std::cout << process.getStderr() << std::endl;
  return 0;
}
```
```sh
$ ./example
2

ls: cannot access '/nonexistent': No such file or directory
```

## Example: Commands that do not exist
```cpp
#include <BoosterSeat/process.hpp>
#include <iostream>

int main() {
  bst::Process process("this_command_does_not_exist", {});
  process.waitToComplete();

  std::cout << process.getExitCode() << std::endl;
  std::cout << process.getStdout() << std::endl;
  std::cout << process.getStderr() << std::endl;
  return 0;
}
```
```sh
$ ./example
22

bst_process: execvp() failed: No such file or directory
```

## Example: Command timeout
```cpp
#include <BoosterSeat/process.hpp>
#include <iostream>

int main() {
  try {
    bst::Process process("sleep", {"2"});
    process.waitToComplete(); // default timeout is 1000ms
  } catch (bst::BoosterSeatException &e) {
    std::cout << e.what() << std::endl;
  }
  return 0;
}
```
```sh
$ ./example
BST Errno: 14 | process timed out
```