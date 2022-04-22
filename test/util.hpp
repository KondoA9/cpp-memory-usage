#pragma once

#include <functional>
#include <iostream>
#include <string>

namespace a9 {
    namespace test {
        namespace util {
            enum class Unit {
                Byte,
                KB,
                MB,
                GB,
            };

            void SetUnit(Unit unit);

            void PrintSeparator();

            void PrintNumber(const std::string& label, size_t number, const char* unit);

            void PrintNumber(const std::string& label, double number, const char* unit);

            void PrintMemory(const std::string& label, const std::function<size_t()>& func);
        }
    }
}
