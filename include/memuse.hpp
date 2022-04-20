#pragma once

#if _WIN32 || WIN64
#include "memuse/memuse_win.hpp"
#elif __MACH__
#include "memuse/memuse_mac.hpp"
#elif __unix__ || __linux__
#include "memuse/memuse_linux.hpp"
#else
#endif
