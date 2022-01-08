#include "version.hpp"
#include "current_version.hpp"
#include <sstream>

namespace at
{


std::ostream& operator<<(std::ostream& stream, const engine_version& version)
{
    stream << version.year() << '.' << version.release() << '.';

    switch(version.phase())
    {
        case engine_version_phases::stable:
            break;
        case engine_version_phases::development:
            stream << ".dev";
            break;
        case engine_version_phases::candidate:
            stream << ".candidate";
            break;
    }

    return stream;
}

engine_version linked_version() noexcept
{
    return current_version;
}

}