#include <vector>

#include "memuse.hpp"
#include "util.hpp"

int main() {
    a9::test::util::SetUnit(a9::test::util::Unit::MB);

    std::cout << "cpp-memory-usage v" << CPP_MEMORY_USAGE_VERSION_STRING << std::endl;
    a9::test::util::PrintSeparator();

    a9::test::util::PrintMemory("Total physical memory", a9::memory::GetTotalPhysicalMemory);
    a9::test::util::PrintNumber("Memory usage", a9::memory::GetMemoryUsage(), "%");
    a9::test::util::PrintSeparator();

    std::vector<size_t> vec(1000000);
    a9::test::util::PrintMemory("Process physical usage", a9::memory::GetProcessPhysicalMemoryUsage);
    a9::test::util::PrintSeparator();

    {
        std::vector<size_t> vec2(1000000);
        a9::test::util::PrintMemory("Process physical usage", a9::memory::GetProcessPhysicalMemoryUsage);
        a9::test::util::PrintSeparator();
    }

    std::vector<size_t> vec3(1000000);
    a9::test::util::PrintMemory("Process physical usage", a9::memory::GetProcessPhysicalMemoryUsage);
    a9::test::util::PrintSeparator();

    return 0;
}
