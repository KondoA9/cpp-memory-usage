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

Sample code is [here](https://github.com/KondoA9/cpp-memory-usage/blob/main/test/main.cpp).

> If you do not want to use inline functions, you can define without inlining by difining `CPP_MEMORY_USAGE_NO_INLINE` before `#include memuse.hpp"`.
