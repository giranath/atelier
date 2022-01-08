#include "opengl45_gpu_device.hpp"
#include "opengl45_gpu_pipeline_state.hpp"
#include "opengl45_gpu_buffer.hpp"
#include "opengl45_gpu_texture.hpp"
#include "opengl45_helpers.hpp"

#include <cassert>

namespace at
{

// TODO: Check if glad needs to be loaded inside this library
//       Needs to test on windows with a DLL build

std::unique_ptr<gpu_buffer> opengl45_gpu_device::make_buffer(const gpu_buffer_description& description)
{
    return opengl45_gpu_buffer::make_from_description(description);
}

void opengl45_gpu_device::bind_vertex_buffer(gpu_buffer& buffer, std::size_t offset)
{
    opengl45_gpu_buffer& opengl_buffer = static_cast<opengl45_gpu_buffer&>(buffer);

    if(last_bound_pipeline_state_)
    {
        last_bound_pipeline_state_->bind_vertex_buffer(opengl_buffer.handle(), static_cast<GLintptr>(offset));
    }
}

void opengl45_gpu_device::bind_index_buffer(gpu_buffer& buffer)
{
    opengl45_gpu_buffer& opengl_buffer = static_cast<opengl45_gpu_buffer&>(buffer);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, opengl_buffer.handle());
}

std::unique_ptr<gpu_pipeline_state> opengl45_gpu_device::make_pipeline_state(const gpu_pipeline_state_description& description)
{
    return opengl45_gpu_pipeline_state::make_from_description(description);
}

void opengl45_gpu_device::bind_pipeline_state(gpu_pipeline_state& state)
{
    opengl45_gpu_pipeline_state& opengl_state = static_cast<opengl45_gpu_pipeline_state&>(state);

    opengl_state.bind();

    last_bound_pipeline_state_ = &opengl_state;
}

std::unique_ptr<gpu_texture> opengl45_gpu_device::make_texture2d(const gpu_texture2d_description& description)
{
    return opengl45_gpu_texture::make_from_description(description);
}

void opengl45_gpu_device::bind_texture(gpu_texture& texture, int binding)
{
    opengl45_gpu_texture& opengl_texture = static_cast<opengl45_gpu_texture&>(texture);

    glActiveTexture(GL_TEXTURE0 + binding);
    glBindTexture(GL_TEXTURE_2D, opengl_texture.handle());
}

void opengl45_gpu_device::clear_render_target(float r, float g, float b)
{
    glClearColor(r, g, b, 1.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void opengl45_gpu_device::draw(const gpu_draw_description& description)
{
    if(description.is_indexed)
    {
        const GLsizei index_type_size = gl_index_type_size(description.index_type);

        glDrawElements(gl_draw_topology(description.topology),
                       description.count,
                       gl_index_type(description.index_type),
                       reinterpret_cast<GLvoid*>(index_type_size * description.offset));
    }
    else
    {
        glDrawArrays(gl_draw_topology(description.topology),
                     description.offset,
                     description.count);
    }
}

}