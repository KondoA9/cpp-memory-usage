#pragma once

#include <mach/mach.h>
#include <sys/sysctl.h>

namespace a9 {
    namespace memory {
        // Return memory usage [%]
        size_t GetMemoryUsage() {
            return 0;
        }

        // Return total physical memory [byte]
        size_t GetTotalPhysicalMemory() {
            int mib[2]    = {CTL_HW, HW_MEMSIZE};
            int64_t total = 0;
            size_t length = sizeof(total);

            sysctl(mib, 2, &total, &length, NULL, 0);

            return static_cast<size_t>(total);
        }

        // Return RSS [byte]
        // The value may be incorrect
        size_t GetProcessMemoryUsage() {
            task_t targetTask = mach_task_self();
            task_basic_info ti;
            mach_msg_type_number_t count = TASK_BASIC_INFO_64_COUNT;

            const auto result = task_info(targetTask, TASK_BASIC_INFO_64, (task_info_t)&ti, &count);
            if (result == KERN_SUCCESS) {
                return ti.resident_size;
            } else {
                return 0;
            }
        }
    }
}
