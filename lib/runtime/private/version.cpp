#include "version.hpp"
#include "current_version.hpp"

namespace at
{
    
void linked_version(int& out_year, int& out_increment) noexcept
{
    out_year = current_version.year;
    out_increment = current_version.revision;
}

const char* linked_version_c_str() noexcept
{
    return current_version.c_str;
}

}