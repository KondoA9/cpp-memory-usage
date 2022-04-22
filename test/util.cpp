#include "util.hpp"

namespace a9 {
    namespace test {
        namespace util {
            auto unit = Unit::MB;

            namespace _internal {
                const char* GetUnitString() {
                    return unit == Unit::Byte ? "Byte"
                           : unit == Unit::KB ? "KB"
                           : unit == Unit::MB ? "MB"
                           : unit == Unit::GB ? "GB "
                                              : "TB";
                }

                uint32_t GetUnitDivider() {
                    return unit == Unit::Byte ? 1
                           : unit == Unit::KB ? 1024
                           : unit == Unit::MB ? 1024 * 1024
                                              : 1024 * 1024 * 1024;
                }
            }

            auto unitString  = _internal::GetUnitString();
            auto unitDivider = _internal::GetUnitDivider();

            void SetUnit(Unit _unit) {
                unit        = _unit;
                unitString  = _internal::GetUnitString();
                unitDivider = _internal::GetUnitDivider();
            }

            void PrintSeparator() {
                std::cout << "---------------------------------------------------------" << std::endl;
            }

            void PrintNumber(const std::string& label, size_t number, const char* unitName) {
                std::cout << label << ": " << number << " " << unitName << std::endl;
            }

            void PrintNumber(const std::string& label, double number, const char* unitName) {
                std::cout << label << ": " << number << " " << unitName << std::endl;
            }

            void PrintMemory(const std::string& label, const std::function<size_t()>& func) {
                PrintNumber(label, static_cast<double>(func()) / static_cast<double>(unitDivider), unitString);
            }
        }
    }
}
