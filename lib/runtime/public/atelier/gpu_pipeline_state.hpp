#ifndef ATELIER_GPU_PIPELINE_HPP
#define ATELIER_GPU_PIPELINE_HPP

#include "runtime_export.hpp"
#include "gpu_vertex_layout.hpp"
#include <string>

namespace at
{

/**
 * Describe a single stage of the pipeline
 */
struct ATELIER_RUNTIME_EXPORT gpu_pipeline_stage_description
{
    std::string shader_source;
    bool enabled;
};

/**
 * Describe a gpu pipeline state
 */
struct ATELIER_RUNTIME_EXPORT gpu_pipeline_state_description
{
    gpu_vertex_layout vertex_layout;
    gpu_pipeline_stage_description vertex_stage;
    gpu_pipeline_stage_description fragment_stage;
};

/**
 * Interface representing a state of the GPU pipeline
 * The state is responsible to represent:
 *  - the layout of a vertex
 *  - shader program to use
 */
struct ATELIER_RUNTIME_EXPORT gpu_pipeline_state
{
    virtual ~gpu_pipeline_state() = default;

    /**
     * Returns the vertex layout used by this pipeline state
     * @return The vertex layout used by this pipeline state
     */
    virtual const gpu_vertex_layout& vertex_layout() const = 0;

    /**
     * The stride of a vertex
     * @return The stride of a vertex
     */
    virtual std::size_t vertex_stride() const = 0;
};

}

#endif
