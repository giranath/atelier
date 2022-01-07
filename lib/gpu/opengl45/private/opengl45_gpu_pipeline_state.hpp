#ifndef ATELIER_OPENGL45_GPU_PIPELINE_STATE_HPP
#define ATELIER_OPENGL45_GPU_PIPELINE_STATE_HPP

#include <atelier/gpu_pipeline_state.hpp>
#include <glad/glad.h>
#include <memory>

namespace at
{

class opengl45_gpu_pipeline_state final : public gpu_pipeline_state
{
    GLuint vao_ = 0;
    GLuint program_ = 0;
    GLuint stride_ = 0;
    gpu_vertex_layout vertex_layout_ = {};

public:
    opengl45_gpu_pipeline_state() = default;
    ~opengl45_gpu_pipeline_state();

    const gpu_vertex_layout& vertex_layout() const override final;
    std::size_t vertex_stride() const override final;

    void bind();
    void bind_vertex_buffer(GLuint buffer, GLintptr offset);

    static std::unique_ptr<opengl45_gpu_pipeline_state> make_from_description(const gpu_pipeline_state_description& description);
};

}

#endif
