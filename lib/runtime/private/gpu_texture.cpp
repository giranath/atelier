#include "gpu_texture.hpp"

namespace at
{

gpu_texture2d_description::gpu_texture2d_description() noexcept
: pixels{nullptr}
, width{0}
, height{0}
, format{gpu_texture_format::rgb8}
, filtering{gpu_texture_filtering::bilinear}
, wrapping{gpu_texture_wrapping::clamp}
, generate_mipmaps{false}
{

}

gpu_texture2d_description::gpu_texture2d_description(uint32_t width, uint32_t height, gpu_texture_format format, const void* pixels) noexcept
: pixels{pixels}
, width{width}
, height{height}
, format{format}
, filtering{gpu_texture_filtering::bilinear}
, wrapping{gpu_texture_wrapping::clamp}
, generate_mipmaps{false}
{

}

}