#ifndef ATELIER_RUNTIME_GPU_BUFFER_HPP
#define ATELIER_RUNTIME_GPU_BUFFER_HPP

#include "runtime_export.hpp"
#include <cstddef>

namespace at
{

/**
 * Describe a memory buffer to allocate on the GPU
 */
struct ATELIER_RUNTIME_EXPORT gpu_buffer_description
{
    std::size_t size = 0;
    const void* initial_memory = nullptr;
    bool enable_read_mapping = false;
    bool enable_write_mapping = false;

    gpu_buffer_description() = default;
};

/**
 * Base interface to interact with a gpu buffer
 */
struct ATELIER_RUNTIME_EXPORT gpu_buffer
{
    virtual ~gpu_buffer() = default;

    /**
     * Map the GPU memory in readonly
     * @return The address of the mapped memory
     */
    virtual const void* map_read() = 0;

    /**
     * Map the GPU memory in write
     * @return The address of the mapped memory
     */
    virtual void* map_write() = 0;

    /**
     * Unmap the buffer
     */
    virtual void unmap() = 0;

    /**
     * Returns the size of the buffer
     * @return The size of the buffer
     */
    virtual std::size_t size() const = 0;
};

}

#endif
