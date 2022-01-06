#ifndef DEF_ATELIER_RUNTIME_FRAME_DURATION_HPP
#define DEF_ATELIER_RUNTIME_FRAME_DURATION_HPP

#include <chrono>

namespace at
{

/**
 * Represents the duration of a frame in seconds
 */
using frame_duration = std::chrono::duration<double>;

}

#endif
