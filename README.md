# Stopwatch

Stopwatch is a simple, fast, cross-platform and header-only stopwatch for C++.

## Build Status

[![Build status](https://ci.appveyor.com/api/projects/status/9k2i690w70l4p64e?svg=true)](https://ci.appveyor.com/project/lishiyu/stopwatch)

## Test

```shell
sudo sh ./build.sh
./test
```

## Usage

- include header

  ```cpp
  #include "stopwatch.hpp"
  ```

- instantiate a class in stack

  ```cpp
  Stopwatch stopwatch;
  ```

- start stopwatch

  ```cpp
  stopwatch.start();
  ```

- split and get duration

  ```cpp
  std::cout << "duration: " << stopwatch.split().count() << " seconds" << std::endl;
  ```

- get current time

  ```cpp
  std::cout << "current_time: " << Stopwatch::current_time << std::endl;
  ```

- stop stopwatch

  ```cpp
  stopwatch.stop();
  ```