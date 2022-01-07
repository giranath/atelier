#ifndef ATELIER_RUNTIME_GPU_TEXTURE_HPP
#define ATELIER_RUNTIME_GPU_TEXTURE_HPP

#include "runtime_export.hpp"
#include <cstdint>

namespace at
{

/**
 * Enumerates every supported texture types
 */
enum class gpu_texture_types : uint8_t
{
    _2d
};

/**
 * Enumerates every supported texture formats
 */
enum class gpu_texture_format : uint8_t
{
    rgba8,
    rgb8
};

/**
 * Enumerates every supported texture filtering modes
 */
enum class gpu_texture_filtering : uint8_t
{
    point,
    bilinear,
    trilinear
};


/**
 * Enumerates every supported texture wrapping modes
 */
enum class gpu_texture_wrapping : uint8_t
{
    clamp,
    repeat,
    mirror
};

/**
 * Describe a 2D texture
 */
struct ATELIER_RUNTIME_EXPORT gpu_texture2d_description
{
    const void* pixels;
    uint32_t width;
    uint32_t height;
    gpu_texture_format format;
    gpu_texture_filtering filtering;
    gpu_texture_wrapping wrapping;
    bool generate_mipmaps;

    gpu_texture2d_description() noexcept;
    gpu_texture2d_description(uint32_t width, uint32_t height, gpu_texture_format format, const void* pixels) noexcept;
};

/**
 * Base interface every texture must implement to be usable by Atelier
 */
struct ATELIER_RUNTIME_EXPORT gpu_texture
{
    virtual ~gpu_texture() = default;

    /**
     * Returns the type of this texture
     * @return The type of this texture
     */
    virtual gpu_texture_types type() const = 0;

    /**
     * Returns the width of the texture
     * @return the width of the texture
     */
    virtual uint32_t width() const = 0;

    /**
     * Returns the height of the texture
     * @return The height of the texture
     */
    virtual uint32_t height() const = 0;

    /**
     * Returns the pixel format of the texture
     * @return The format of the texture
     */
    virtual gpu_texture_format format() const = 0;

    /**
     * Returns the filtering type of the texture
     * @return The filtering type of the texture
     */
    virtual gpu_texture_filtering filtering() const = 0;

    /**
     * Returns the wrapping type of the texture
     * @return The wrapping type of the texture
     */
    virtual gpu_texture_wrapping wrapping() const = 0;

    /**
     * Indicate if the texture has mipmaps
     * @return true when the texture has mipmaps
     */
    virtual bool has_mipmaps() const = 0;
};

}

#endif
