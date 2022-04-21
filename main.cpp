#include <functional>
#include <iostream>
#include <vector>

#include "include/memuse.hpp"

enum class Unit {
    Byte,
    KB,
    MB,
    GB,
    TB,
};

constexpr auto UNIT        = Unit::MB;
constexpr auto UnitString  = UNIT == Unit::Byte ? "Byte"
                             : UNIT == Unit::KB ? "KB"
                             : UNIT == Unit::MB ? "MB"
                             : UNIT == Unit::GB ? "GB "
                                                : "TB";
constexpr auto UnitDivider = UNIT == Unit::Byte ? 1
                             : UNIT == Unit::KB ? 1024
                             : UNIT == Unit::MB ? 1024 * 1024
                             : UNIT == Unit::GB ? 1024 * 1024 * 1024
                                                : 1024 * 1024 * 1024 * 1024;

template <typename T>
void printNumber(const std::string& label, T number, const char* unit) {
    std::cout << label << ": " << number << " " << unit << std::endl;
}

void printMemory(const std::string& label, const std::function<size_t()>& func) {
    printNumber(label, func() / UnitDivider, UnitString);
}

void printSeparator() {
    std::cout << "---------------------------------------------------------" << std::endl;
}

int main() {
    printMemory("Total physical memory", a9::memory::GetTotalPhysicalMemory);
    printMemory("Total virtual memory", a9::memory::GetTotalVirtuallMemory);
    printNumber("Memory usage", a9::memory::GetMemoryUsage(), "%");
    printSeparator();

    std::vector<size_t> vec(1000000);
    printMemory("Process physical usage", a9::memory::GetProcessPhysicalMemoryUsage);
    printMemory("Process virtual usage", a9::memory::GetProcessVirtualMemoryUsage);
    printSeparator();

    {
        std::vector<size_t> vec2(1000000);
        printMemory("Process physical usage", a9::memory::GetProcessPhysicalMemoryUsage);
        printMemory("Process virtual usage", a9::memory::GetProcessVirtualMemoryUsage);
        printSeparator();
    }

    std::vector<size_t> vec3(1000000);
    printMemory("Process physical usage", a9::memory::GetProcessPhysicalMemoryUsage);
    printMemory("Process virtual usage", a9::memory::GetProcessVirtualMemoryUsage);
    printSeparator();

    return 0;
}
