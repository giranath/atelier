#ifndef DEF_ATELIER_CURRENT_VERSION_HPP
#define DEF_ATELIER_CURRENT_VERSION_HPP

namespace at
{

struct engine_version
{
    int year;
    int revision;
    const char* c_str;

    constexpr engine_version(int year, int revision, const char* str) noexcept
    : year{year}
    , revision{revision}
    , c_str{str}
    {

    }
};

static constexpr engine_version current_version{@atelier_VERSION_MAJOR@, @atelier_VERSION_MINOR@, "@atelier_VERSION_MAJOR@.@atelier_VERSION_MINOR@"};

}

#endif