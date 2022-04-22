#pragma once

#include <mach/mach.h>
#include <sys/sysctl.h>

#include "macro.hpp"

namespace a9 {
    namespace memory {
        namespace _internal {
            _CPP_MEMORY_USAGE_INLINE size_t GetPageSize() {
                vm_size_t pagesize;
                if (host_page_size(mach_host_self(), &pagesize) == KERN_SUCCESS) {
                    return pagesize;
                } else {
                    return 0;
                }
            }

            _CPP_MEMORY_USAGE_INLINE vm_statistics_data_t GetHostStatistics() {
                vm_statistics_data_t vmstat;
                mach_msg_type_number_t count = HOST_VM_INFO_COUNT;
                if (host_statistics(mach_host_self(), HOST_VM_INFO, (host_info_t)&vmstat, &count) != KERN_SUCCESS) {
                    return {};
                }

                return vmstat;
            }
        }

        // Return total physical memory [byte]
        _CPP_MEMORY_USAGE_INLINE size_t GetTotalPhysicalMemory() {
            int mib[2]     = {CTL_HW, HW_MEMSIZE};
            uint64_t total = 0;
            size_t length  = sizeof(total);

            sysctl(mib, 2, &total, &length, NULL, 0);

            return static_cast<size_t>(total);
        }

        // Return physical memory usage of the process [byte]
        _CPP_MEMORY_USAGE_INLINE size_t GetProcessPhysicalMemoryUsage() {
            task_t targetTask = mach_task_self();
            task_vm_info_data_t ti;
            mach_msg_type_number_t count = TASK_VM_INFO_COUNT;

            const auto result = task_info(targetTask, TASK_VM_INFO, reinterpret_cast<task_info_t>(&ti), &count);
            if (result == KERN_SUCCESS) {
                return ti.phys_footprint;
            } else {
                return 0;
            }
        }

        // Return memory usage [%]
        _CPP_MEMORY_USAGE_INLINE size_t GetMemoryUsage() {
            const auto pagesize = _internal::GetPageSize();
            const auto vmstat   = _internal::GetHostStatistics();

            const auto freeMem  = (vmstat.free_count + vmstat.inactive_count) * pagesize;
            const auto totalMem = GetTotalPhysicalMemory();

            return 100 * (totalMem - freeMem) / totalMem;
        }
    }
}
