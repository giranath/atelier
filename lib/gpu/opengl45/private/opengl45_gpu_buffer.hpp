#ifndef ATELIER_OPENGL_45_GPU_BUFFER_HPP
#define ATELIER_OPENGL_45_GPU_BUFFER_HPP

#include <atelier/gpu_buffer.hpp>
#include <glad/glad.h>
#include <memory>

namespace at
{

class opengl45_gpu_buffer final : public gpu_buffer
{
    GLuint vbo_;
public:
    ~opengl45_gpu_buffer();

    const void* map_read() override final;
    void* map_write() override final;
    void unmap() override final;
    std::size_t size() const override final;

    GLuint handle() const noexcept;

    static std::unique_ptr<opengl45_gpu_buffer> make_from_description(const gpu_buffer_description& description);
};

}

#endif
