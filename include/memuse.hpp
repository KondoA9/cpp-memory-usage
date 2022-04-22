#pragma once

#define CPP_MEMORY_USAGE_VERSION_MAJOR 0
#define CPP_MEMORY_USAGE_VERSION_MINOR 1
#define CPP_MEMORY_USAGE_VERSION_PATCH 2
#define CPP_MEMORY_USAGE_VERSION_STRING "0.1.2"
#define CPP_MEMORY_USAGE_VERSION                                                                                       \
    (CPP_MEMORY_USAGE_VERSION_MAJOR * 10000 + CPP_MEMORY_USAGE_VERSION_MINOR * 100 + CPP_MEMORY_USAGE_VERSION_PATCH)

#if _WIN32 || WIN64
#include "memuse/memuse_win.hpp"
#elif __MACH__
#include "memuse/memuse_mac.hpp"
#elif __unix__ || __linux__
#include "memuse/memuse_linux.hpp"
#else
#endif
