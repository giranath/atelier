#ifndef DEF_ATELIER_CURRENT_VERSION_HPP
#define DEF_ATELIER_CURRENT_VERSION_HPP

#include "version.hpp"
#include <cstdint>

namespace at
{

constexpr engine_version current_version{@atelier_VERSION_MAJOR@, @atelier_VERSION_MINOR@, engine_version_phases::@ATELIER_RELEASE_PHASE@};

}

#endif