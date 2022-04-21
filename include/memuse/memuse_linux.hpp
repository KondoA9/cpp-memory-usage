#pragma once

#include <string.h>
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

            int ParseLine(const std::string& line) {
                std::string n = "";
                for (const auto& c : line) {
                    if ('0' <= c && c <= '9') {
                        n += c;
                    }
                }
                return std::stoi(n);
            }

            size_t GetValueFromProcStatus(const char* label) {
                const auto len = strlen(label);
                std::ifstream stream("/proc/self/status");
                std::string line;
                size_t result = 0;
                while (getline(stream, line)) {
                    if (line.compare(0, len, label) == 0) {
                        result = static_cast<size_t>(ParseLine(line));
                        break;
                    }
                }

                stream.close();

                return result;
            }
        }

        // Functions in this namespace are not implemented on some platforms.
        namespace platform {
            // Return total virtual memory [byte]
            size_t GetTotalVirtuallMemory() {
                const auto info = _internal::GetSysInfo();
                return (info.totalram + info.totalswap) * info.mem_unit;
            }

            // Return virtual memory usage of the process [byte]
            size_t GetProcessVirtualMemoryUsage() {
                return _internal::GetValueFromProcStatus("VmSize:") * 1024;  // KB to Byte
            }
        }

        // Return total physical memory [byte]
        size_t GetTotalPhysicalMemory() {
            const auto info = _internal::GetSysInfo();
            return info.totalram * info.mem_unit;
        }

        // Return physical memory usage of the process [byte]
        size_t GetProcessPhysicalMemoryUsage() {
            return _internal::GetValueFromProcStatus("VmRSS:") * 1024;  // KB to Byte
        }

        // Return private memory usage [byte]
        size_t GetProcessPrivateMemoryUsage() {
            size_t size = 0, resident = 0, share = 0;

            std::ifstream stream("/proc/self/statm");
            stream >> size >> resident >> share;
            stream.close();

            return static_cast<size_t>((resident - share) * sysconf(_SC_PAGE_SIZE));
        }

        // Return memory usage [%]
        size_t GetMemoryUsage() {
            const auto info       = _internal::GetSysInfo();
            const size_t totalMem = info.totalram * info.mem_unit;
            const size_t useMem   = (info.totalram - info.freeram) * info.mem_unit;
            return useMem / totalMem;
        }
    }
}
