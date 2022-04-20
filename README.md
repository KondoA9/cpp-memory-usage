# cpp-memory-usage

Header only library to get memory usage for windows, macOS, linux.

## Usage

```c++
#include "memuse.hpp"
```

or

```c++
#include "memuse/memuse_{win, mac, linux}"
```

## Example

```c++
// total mechine memory [byte]
std::cout << "total mechine memory: " << a9::memory::GetTotalPhysicalMemory() << " byte" << std::endl;

// mechine memory usage [%]
std::cout << "mechine memory usage: " << a9::memory::GetMemoryUsage() << " %" << std::endl;

// process memory usage [byte]
std::cout << "process memory usage: " << a9::memory::GetProcessMemoryUsage() << " byte" << std::endl;
```
