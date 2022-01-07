#include "opengl45_gpu_texture.hpp"
#include "opengl45_helpers.hpp"

namespace at
{

opengl45_gpu_texture::~opengl45_gpu_texture()
{
    if(texture_ != 0)
    {
        glDeleteTextures(1, &texture_);
    }
}

gpu_texture_types opengl45_gpu_texture::type() const
{
    return type_;
}

uint32_t opengl45_gpu_texture::width() const
{
    return width_;
}

uint32_t opengl45_gpu_texture::height() const
{
    return height_;
}

gpu_texture_format opengl45_gpu_texture::format() const
{
    return format_;
}

gpu_texture_filtering opengl45_gpu_texture::filtering() const
{
    return filtering_;
}

gpu_texture_wrapping opengl45_gpu_texture::wrapping() const
{
    return wrapping_;
}

bool opengl45_gpu_texture::has_mipmaps() const
{
    return has_mipmaps_;
}

GLuint opengl45_gpu_texture::handle() const noexcept
{
    return texture_;
}

std::unique_ptr<opengl45_gpu_texture> opengl45_gpu_texture::make_from_description(const gpu_texture2d_description& description)
{
    std::unique_ptr<opengl45_gpu_texture> new_texture = std::make_unique<opengl45_gpu_texture>();
    new_texture->type_ = gpu_texture_types::_2d;
    glCreateTextures(GL_TEXTURE_2D, 1, &new_texture->texture_);

    // Setup wrapping on new texture
    new_texture->wrapping_ = description.wrapping;
    switch(description.wrapping)
    {
        case gpu_texture_wrapping::clamp:
            glTextureParameteri(new_texture->texture_, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTextureParameteri(new_texture->texture_, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            break;
        case gpu_texture_wrapping::repeat:
            glTextureParameteri(new_texture->texture_, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTextureParameteri(new_texture->texture_, GL_TEXTURE_WRAP_T, GL_REPEAT);
            break;
        case gpu_texture_wrapping::mirror:
            glTextureParameteri(new_texture->texture_, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
            glTextureParameteri(new_texture->texture_, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
            break;
    }

    // Setup filtering on new texture
    new_texture->filtering_ = description.filtering;
    switch(description.filtering)
    {
        case gpu_texture_filtering::point:
            glTextureParameteri(new_texture->texture_, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glTextureParameteri(new_texture->texture_, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            break;
        case gpu_texture_filtering::bilinear:
            glTextureParameteri(new_texture->texture_, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTextureParameteri(new_texture->texture_, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            break;
        case gpu_texture_filtering::trilinear:
            glTextureParameteri(new_texture->texture_, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTextureParameteri(new_texture->texture_, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            break;
    }

    // Allocate memory on GPU for the new texture
    glTextureStorage2D(new_texture->texture_,
                        // The number of texture levels
                        1,
                        // The pixel format of the texture
                        gl_internal_texture_format(description.format),
                        // The dimension of the texture
                        static_cast<GLsizei>(description.width), static_cast<GLsizei>(description.height));

    // TODO: Make pixel upload more configurable
    glTextureSubImage2D(new_texture->texture_, 0, 0, 0, description.width, description.height, GL_RGBA, GL_UNSIGNED_BYTE, description.pixels);

    new_texture->has_mipmaps_ = description.generate_mipmaps;
    if(description.generate_mipmaps)
    {
        glGenerateTextureMipmap(new_texture->texture_);
    }

    return new_texture;
}

}