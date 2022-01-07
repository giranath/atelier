#ifndef ATELIER_RUNTIME_GPU_DEVICE_HPP
#define ATELIER_RUNTIME_GPU_DEVICE_HPP

#include "runtime_export.hpp"

namespace at
{

/**
 * Interface every GPU device must implement to be usable by Atelier
 */
struct ATELIER_RUNTIME_EXPORT gpu_device
{
    virtual ~gpu_device() = default;
};

}

#endif
