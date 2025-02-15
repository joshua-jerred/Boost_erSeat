# [BST Module] Profiler

The profiler module is a tool to measure performance across a call stack. It was
made to be hardware generic, but this means that it is only as accurate as it's
time source.

## Usage

```c++
#include <bst/profiler.hpp>

int main() {
  // The singleton profiler instance. This must be created before any events are
  // created.
  bst::Profiler profiler;

  // The event will automatically stop when it goes out of scope
  bst::Profiler::Event event{"main"};

  {
    bst::Profiler::Event inner_scope{"inner_scope"};

    bst::Profiler::Event task1{"task1"};
    // - work to be profiled -
    task1.stop(); // Stop the task manually, instead of waiting for the destructor

    bst::Profiler::Event task2{"task2"};
    // - work to be profiled -
  }
  // The `.stop()` method for `inner_scope` and `task2` were called above 
  // automatically when the destructors were called, as they went out of scope.

  // Print the results
  std::cout << profiler.getReportText() << std::endl;
  std::cout << profiler.getReportJson() << std::endl;
}
```
**Report Text Output:**
```shell
main: 0.000000s
  inner_scope: 0.000000s
    task1: 0.000000s
    task2: 0.000000s
```

**Report JSON Output:**
```json
{
  "event_tree": [
    {
      "name": "main",
      "duration_us": 0,
      "children": [
        {
          "name": "inner_scope",
          "duration_us": 0,
          "children": [
            {
              "name": "task1",
              "duration_us": 0,
              "children": []
            },
            {
              "name": "task2",
              "duration_us": 0,
              "children": []
            }
          ]
        }
      ]
    }
  ]
}
```