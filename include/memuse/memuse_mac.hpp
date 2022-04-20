#pragma once

#include <mach/mach.h>
#include <sys/sysctl.h>

namespace a9 {
    namespace memory {
        namespace _internal {
            size_t GetPageSize() {
                vm_size_t pagesize;
                if (host_page_size(mach_host_self(), &pagesize) == KERN_SUCCESS) {
                    return pagesize;
                } else {
                    return 0;
                }
            }

            vm_statistics_data_t GetHostStatistics() {
                vm_statistics_data_t vmstat;
                mach_msg_type_number_t count = HOST_VM_INFO_COUNT;
                if (host_statistics(mach_host_self(), HOST_VM_INFO, (host_info_t)&vmstat, &count) != KERN_SUCCESS) {
                    return {};
                }

                return vmstat;
            }
        }

        // Return total physical memory [byte]
        size_t GetTotalPhysicalMemory() {
            int mib[2]     = {CTL_HW, HW_MEMSIZE};
            uint64_t total = 0;
            size_t length  = sizeof(total);

            sysctl(mib, 2, &total, &length, NULL, 0);

            return static_cast<size_t>(total);
        }

        // Return memory usage [%]
        size_t GetMemoryUsage() {
            const auto pagesize = _internal::GetPageSize();
            const auto vmstat   = _internal::GetHostStatistics();

            const auto freeMem  = (vmstat.free_count + vmstat.inactive_count) * pagesize;
            const auto totalMem = GetTotalPhysicalMemory();

            return 100 * (totalMem - freeMem) / totalMem;
        }

        // Return RSS [byte]
        // The value may be incorrect
        size_t GetProcessMemoryUsage() {
            task_t targetTask = mach_task_self();
            task_basic_info ti;
            mach_msg_type_number_t count = TASK_BASIC_INFO_64_COUNT;

            const auto result = task_info(targetTask, TASK_BASIC_INFO_64, reinterpret_cast<task_info_t>(&ti), &count);
            if (result == KERN_SUCCESS) {
                return ti.resident_size;
            } else {
                return 0;
            }
        }
    }
}
