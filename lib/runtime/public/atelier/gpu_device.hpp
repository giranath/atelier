#ifndef ATELIER_RUNTIME_GPU_DEVICE_HPP
#define ATELIER_RUNTIME_GPU_DEVICE_HPP

#include "runtime_export.hpp"
#include <memory>

namespace at
{

struct gpu_pipeline_state;
struct gpu_pipeline_state_description;
struct gpu_buffer;
struct gpu_buffer_description;
struct gpu_texture;
struct gpu_texture2d_description;

/**
 * Enumerates supported draw topologies
 */
enum class gpu_draw_topology : uint8_t
{
    triangles
};

/**
 * Enumerates supported index types
 */
enum class gpu_index_types : uint8_t
{
    uint8,
    uint16,
    uint32
};

/**
 * Describe a draw command
 */
struct ATELIER_RUNTIME_EXPORT gpu_draw_description
{
    uint32_t count = 0;
    uint32_t offset = 0;
    bool is_indexed = false;
    gpu_index_types index_type = gpu_index_types::uint8;
    gpu_draw_topology topology = gpu_draw_topology::triangles;

    gpu_draw_description() = default;
};

/**
 * Interface every GPU device must implement to be usable by Atelier
 */
struct ATELIER_RUNTIME_EXPORT gpu_device
{
    virtual ~gpu_device() = default;

    /**
     * Allocate a new memory buffer on GPU
     * @param description A description of the memory buffer to allocate
     * @return the new instance of memory buffer
     */
    virtual std::unique_ptr<gpu_buffer> make_buffer(const gpu_buffer_description& description) = 0;

    /**
     * Bind a vertex buffer
     * @param buffer The buffer to bind as a vertex buffer
     * @param offset The offset to bind from
     */
    virtual void bind_vertex_buffer(gpu_buffer& buffer, std::size_t offset = 0) = 0;

    /**
     * Bind an index buffer
     * @param buffer The buffer to bind
     */
    virtual void bind_index_buffer(gpu_buffer& buffer) = 0;

    /**
     * Make an instance of a pipeline state
     * @param description A description of the pipeline state to create
     * @return The new instance of the pipeline state
     */
    virtual std::unique_ptr<gpu_pipeline_state> make_pipeline_state(const gpu_pipeline_state_description& description) = 0;

    /**
     * Bind a pipeline state
     * @param state The state to bind
     */
    virtual void bind_pipeline_state(gpu_pipeline_state& state) = 0;

    /**
     * Make a 2D texture
     * @param description A description of the texture to make
     * @return the created texture
     */
    virtual std::unique_ptr<gpu_texture> make_texture2d(const gpu_texture2d_description& description) = 0;

    /**
     * Bind a texture
     * @param texture The texture to bind
     * @param binding The binding point of the texture
     */
    virtual void bind_texture(gpu_texture& texture, int binding) = 0;

    /**
     * Clear current render target
     * @param r Red component
     * @param g Green component
     * @param b Blue component
     */
    virtual void clear_render_target(float r, float g, float b) = 0;

    /**
     * Send draw command to the GPU
     */
    virtual void draw(const gpu_draw_description& description) = 0;
};

}

#endif
