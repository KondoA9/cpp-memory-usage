#pragma once

// clang-format off
#include <windows.h>
// clang-format on

#include <Psapi.h>

namespace a9 {
    namespace memory {
        namespace _internal {
            MEMORYSTATUSEX GetMemoryStatus() {
                MEMORYSTATUSEX status;
                status.dwLength = sizeof(status);
                GlobalMemoryStatusEx(&status);
                return status;
            }

            PROCESS_MEMORY_COUNTERS_EX GetMemoryInfo() {
                const HANDLE hProcess = GetCurrentProcess();

                PROCESS_MEMORY_COUNTERS_EX pmc = {0};

                GetProcessMemoryInfo(hProcess, reinterpret_cast<PROCESS_MEMORY_COUNTERS*>(&pmc), sizeof(pmc));

                return pmc;
            }
        }

        // Return total physical memory [byte]
        size_t GetTotalPhysicalMemory() {
            return _internal::GetMemoryStatus().ullTotalPhys;
        }

        // Return total virtual memory [byte]
        size_t GetTotalVirtuallMemory() {
            return _internal::GetMemoryStatus().ullTotalPageFile;
        }

        // Return physical memory usage [byte]
        size_t GetProcessPhysicalMemoryUsage() {
            return _internal::GetMemoryInfo().WorkingSetSize;
        }

        // Return virtual memory usage of the process [byte]
        size_t GetProcessVirtualMemoryUsage() {
            return _internal::GetMemoryInfo().PrivateUsage;
        }

        // Return memory usage [%]
        size_t GetMemoryUsage() {
            return _internal::GetMemoryStatus().dwMemoryLoad;
        }
    }
}
