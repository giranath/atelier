#ifndef ATELIER_RUNTIME_VERSION_HPP
#define ATELIER_RUNTIME_VERSION_HPP

#include "runtime_export.hpp"

namespace at
{
    
/**
 * Returns the linked version of the engine
 * @param out_year The year of the version
 * @param out_increment The year's increment version
 * @note Atelier version schema is year.increment, the engine cannot guarantee a stable ABI so instead of using semver is uses this custom format
 *       There is no guarantee on the stability of the API, but the engine will try its best to correctly deprecate its API in a progressive way
 */
ATELIER_RUNTIME_EXPORT void linked_version(int& out_year, int& out_increment) noexcept;

/**
 * Returns the string representation of the current version of the engine
 * @return The string representation of the current version of the engine
 */
ATELIER_RUNTIME_EXPORT const char* linked_version_c_str() noexcept;

}

#endif