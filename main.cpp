#include <iostream>
#include <vector>

#include "include/memuse.hpp"

int main() {
    std::vector<size_t> vec(1000000);

    std::cout << "total machine memory: " << a9::memory::GetTotalPhysicalMemory() << " byte" << std::endl;
    std::cout << "machine memory usage: " << a9::memory::GetMemoryUsage() << " %" << std::endl;
    std::cout << "process memory usage: " << a9::memory::GetProcessMemoryUsage() << " byte" << std::endl;

    {
        std::vector<size_t> vec2(1000000);
        std::cout << "process memory usage: " << a9::memory::GetProcessMemoryUsage() << " byte" << std::endl;
    }

    std::vector<size_t> vec3(1000000);
    std::cout << "process memory usage: " << a9::memory::GetProcessMemoryUsage() << " byte" << std::endl;

    return 0;
}
