#pragma once

#include <sys/sysinfo.h>
#include <unistd.h>

#include <fstream>

namespace a9 {
    namespace memory {
        namespace _internal {
            struct sysinfo GetSysInfo() {
                struct sysinfo memInfo;
                sysinfo(&memInfo);
                return memInfo;
            }
        }

        // Return total physical memory [byte]
        size_t GetTotalPhysicalMemory() {
            const auto info = _internal::GetSysInfo();
            return info.totalram * info.mem_unit;
        }

        // Return memory usage [%]
        size_t GetMemoryUsage() {
            const auto info       = _internal::GetSysInfo();
            const size_t totalMem = info.totalram * info.mem_unit;
            const size_t useMem   = (info.totalram - info.freeram) * info.mem_unit;
            return useMem / totalMem;
        }

        // Return private memory usage [byte]
        size_t GetProcessMemoryUsage() {
            size_t size = 0, resident = 0, share = 0;

            std::ifstream stream("/proc/self/statm");
            stream >> size >> resident >> share;
            stream.close();

            return static_cast<size_t>((resident - share) * sysconf(_SC_PAGE_SIZE));
        }
    }
}
