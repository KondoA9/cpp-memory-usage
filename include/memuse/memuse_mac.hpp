#pragma once

namespace a9 {
    namespace memory {
        // Return memory usage [%]
        size_t GetMemoryUsage() {
            return 0;
        }

        // Return total physical memory [byte]
        size_t GetTotalPhysicalMemory() {
            return 0;
        }

        // Return private memory usage [byte]
        size_t GetProcessMemoryUsage() {
            return 0;
        }
    }
}
