#include "opengl45_gpu_buffer.hpp"

namespace at
{

opengl45_gpu_buffer::~opengl45_gpu_buffer()
{
    if(vbo_ != 0)
    {
        glDeleteBuffers(1, &vbo_);
    }
}

const void* opengl45_gpu_buffer::map_read()
{
    return glMapNamedBuffer(vbo_, GL_READ_ONLY);
}

void* opengl45_gpu_buffer::map_write()
{
    return glMapNamedBuffer(vbo_, GL_READ_WRITE);
}

void opengl45_gpu_buffer::unmap()
{
    glUnmapNamedBuffer(vbo_);
}

std::size_t opengl45_gpu_buffer::size() const
{
    GLint buffer_size;
    glGetNamedBufferParameteriv(vbo_, GL_BUFFER_SIZE, &buffer_size);

    return buffer_size;
}

GLuint opengl45_gpu_buffer::handle() const noexcept
{
    return vbo_;
}

std::unique_ptr<opengl45_gpu_buffer> opengl45_gpu_buffer::make_from_description(const gpu_buffer_description& description)
{
    std::unique_ptr<opengl45_gpu_buffer> new_buffer = std::make_unique<opengl45_gpu_buffer>();
    glCreateBuffers(1, &new_buffer->vbo_);

    GLbitfield storage_flags = 0;

    if(description.enable_read_mapping)
    {
        storage_flags |= GL_MAP_READ_BIT;
    }

    if(description.enable_write_mapping)
    {
        storage_flags |= GL_MAP_WRITE_BIT;
    }

    glNamedBufferStorage(new_buffer->vbo_, description.size, description.initial_memory, storage_flags);

    return new_buffer;
}

}