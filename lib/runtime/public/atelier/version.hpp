#ifndef ATELIER_RUNTIME_VERSION_HPP
#define ATELIER_RUNTIME_VERSION_HPP

#include "runtime_export.hpp"
#include <cstdint>
#include <iostream>

namespace at
{

enum class engine_version_phases : uint8_t
{
    stable,
    candidate,
    development
};

class ATELIER_RUNTIME_EXPORT engine_version
{
    uint32_t year_;
    uint32_t release_;
    engine_version_phases phase_;
public:
    constexpr engine_version(uint32_t year, uint32_t release, engine_version_phases phase = engine_version_phases::stable) noexcept
    : year_{year}
    , release_{release}
    , phase_{phase}
    {

    }

    [[nodiscard]] constexpr uint32_t year() const noexcept
    {
        return year_;
    }

    [[nodiscard]] constexpr uint32_t release() const noexcept
    {
        return release_;
    }

    [[nodiscard]] constexpr engine_version_phases phase() const noexcept
    {
        return phase_;
    }
};

std::ostream& operator<<(std::ostream& stream, const engine_version& version);

/**
 * Returns the linked version of the engine
 * @return The current linked version of the engine
 * @note Atelier version schema is year.increment, the engine cannot guarantee a stable ABI so instead of using semver is uses this custom format
 *       There is no guarantee on the stability of the API, but the engine will try its best to correctly deprecate its API in a progressive way
 */
ATELIER_RUNTIME_EXPORT engine_version linked_version() noexcept;

}

#endif