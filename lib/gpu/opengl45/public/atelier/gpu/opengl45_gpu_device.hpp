#ifndef ATELIER_GPU_OPENGL45_GPU_DEVICE_HPP
#define ATELIER_GPU_OPENGL45_GPU_DEVICE_HPP

#include "gpu_opengl45_export.hpp"
#include <atelier/gpu_device.hpp>

namespace at
{

class opengl45_gpu_pipeline_state;

/**
 * OpenGL 4.5 Core implementation of the GPU device interface
 */
class ATELIER_GPU_OPENGL45_EXPORT opengl45_gpu_device final : public gpu_device
{
    opengl45_gpu_pipeline_state* last_bound_pipeline_state_;
public:
    std::unique_ptr<gpu_buffer> make_buffer(const gpu_buffer_description& description) override final;
    void bind_vertex_buffer(gpu_buffer& buffer, std::size_t offset) override final;
    void bind_index_buffer(gpu_buffer& buffer, std::size_t size, std::size_t offset) override final;

    std::unique_ptr<gpu_pipeline_state> make_pipeline_state(const gpu_pipeline_state_description& description) override final;
    void bind_pipeline_state(gpu_pipeline_state& state) override final;

    std::unique_ptr<gpu_texture> make_texture2d(const gpu_texture2d_description& description) override final;
    void bind_texture(gpu_texture& texture, int binding) override final;
};

}

#endif
