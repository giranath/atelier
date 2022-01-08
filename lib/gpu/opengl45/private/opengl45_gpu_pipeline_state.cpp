#include "opengl45_gpu_pipeline_state.hpp"
#include "opengl45_helpers.hpp"

namespace at
{

opengl45_gpu_pipeline_state::~opengl45_gpu_pipeline_state()
{
    if(vao_ != 0)
    {
        glDeleteVertexArrays(1, &vao_);
    }
}

const gpu_vertex_layout& opengl45_gpu_pipeline_state::vertex_layout() const
{
    return vertex_layout_;
}

std::size_t opengl45_gpu_pipeline_state::vertex_stride() const
{
    return stride_;
}

void opengl45_gpu_pipeline_state::bind()
{
    glBindVertexArray(vao_);
    glUseProgram(program_);
}

void opengl45_gpu_pipeline_state::bind_vertex_buffer(GLuint buffer, GLintptr offset)
{
    glVertexArrayVertexBuffer(vao_, 0, buffer, offset, stride_);
}

std::unique_ptr<opengl45_gpu_pipeline_state> opengl45_gpu_pipeline_state::make_from_description(const gpu_pipeline_state_description& description)
{
    std::unique_ptr<opengl45_gpu_pipeline_state> new_pipeline_state = std::make_unique<opengl45_gpu_pipeline_state>();
    new_pipeline_state->vao_ = make_vertex_array_from_layout(description.vertex_layout, new_pipeline_state->stride_);
    new_pipeline_state->vertex_layout_ = description.vertex_layout;
    new_pipeline_state->program_ = gl_link_program(description);

    return new_pipeline_state;
}

}