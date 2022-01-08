#ifndef ATELIER_STRING_NAME_HPP
#define ATELIER_STRING_NAME_HPP

#include "runtime_export.hpp"
#include <string_view>
#include <string>

namespace at
{

/**
 * String with a O(1) equality comparison
 * Useful to represent keys in data structure
 */
class ATELIER_RUNTIME_EXPORT string_name
{
    class string_table_entry* entry_;
public:
    string_name();
    string_name(std::string_view str);

    string_name(const string_name& other) noexcept;
    string_name(string_name&& other) noexcept;

    ~string_name();

    string_name& operator=(const string_name& other) noexcept;
    string_name& operator=(string_name&& other) noexcept;

    bool operator==(const string_name& other) const noexcept;
    bool operator!=(const string_name& other) const noexcept;

    void clear() noexcept;

    [[nodiscard]] const char* c_str() const noexcept;
    [[nodiscard]] std::string string() const noexcept;
    [[nodiscard]] bool empty() const noexcept;
};

namespace literals
{

/**
 * Create a string_name from a string literal
 * @param str The string to convert into a string_name
 * @param len The len of the string
 * @return The string_name
 */
string_name operator""_sname(const char* str, std::size_t len);

}

}

#endif
