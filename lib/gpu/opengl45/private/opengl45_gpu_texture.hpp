#ifndef ATELIER_OPENGL45_GPU_TEXTURE_HPP
#define ATELIER_OPENGL45_GPU_TEXTURE_HPP

#include <atelier/gpu_texture.hpp>
#include <glad/glad.h>
#include <memory>

namespace at
{

class opengl45_gpu_texture final : public gpu_texture
{
    uint32_t width_ = 0;
    uint32_t height_ = 0;
    GLuint texture_ = 0;
    bool has_mipmaps_ = false;
    gpu_texture_format format_ = gpu_texture_format::rgba8;
    gpu_texture_filtering filtering_ = gpu_texture_filtering::bilinear;
    gpu_texture_wrapping wrapping_ = gpu_texture_wrapping::clamp;
    gpu_texture_types type_ = gpu_texture_types::_2d;
public:
    opengl45_gpu_texture() = default;
    ~opengl45_gpu_texture();

    virtual gpu_texture_types type() const override final;
    virtual uint32_t width() const override final;
    virtual uint32_t height() const override final;
    virtual gpu_texture_format format() const override final;
    virtual gpu_texture_filtering filtering() const override final;
    virtual gpu_texture_wrapping wrapping() const override final;
    virtual bool has_mipmaps() const override final;

    GLuint handle() const noexcept;

    static std::unique_ptr<opengl45_gpu_texture> make_from_description(const gpu_texture2d_description& description);
};

}

#endif
