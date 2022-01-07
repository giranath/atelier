#include "gpu_vertex_layout.hpp"
#include <stdexcept>
#include <cassert>

namespace at
{


gpu_vertex_attribute::gpu_vertex_attribute() noexcept
: name{}
, type{gpu_vertex_attribute_type::float1}
, is_normalized{false}
{

}

gpu_vertex_attribute::gpu_vertex_attribute(std::string_view name, gpu_vertex_attribute_type type, bool normalized) noexcept
: name{name}
, type{type}
, is_normalized{normalized}
{

}

bool gpu_vertex_attribute::operator==(const gpu_vertex_attribute& other) const noexcept
{
    return type == other.type
        && is_normalized == other.is_normalized
        && name == other.name;
}

bool gpu_vertex_attribute::operator!=(const gpu_vertex_attribute& other) const noexcept
{
    return type != other.type
        || is_normalized != other.is_normalized
        || name != other.name;
}

gpu_vertex_layout::gpu_vertex_layout() noexcept
: attributes_{}
, attribute_count_{0}
{

}

bool gpu_vertex_layout::operator==(const gpu_vertex_layout& other) const noexcept
{
    return attribute_count_ == other.attribute_count_
        && std::equal(attributes_ + 0, attributes_ + attribute_count_, other.attributes_ + 0);
}

bool gpu_vertex_layout::operator!=(const gpu_vertex_layout& other) const noexcept
{
    return attribute_count_ != other.attribute_count_
        && !std::equal(attributes_ + 0, attributes_ + attribute_count_, other.attributes_ + 0);
}

const gpu_vertex_attribute& gpu_vertex_layout::operator[](std::size_t index) const noexcept
{
    assert(index < attribute_count_);

    return attributes_[index];
}

const gpu_vertex_attribute* gpu_vertex_layout::data() const noexcept
{
    return attributes_ + 0;
}

std::size_t gpu_vertex_layout::size() const noexcept
{
    return attribute_count_;
}

gpu_vertex_layout_builder gpu_vertex_layout_builder::make()
{
    return gpu_vertex_layout_builder{};
}

gpu_vertex_layout_builder& gpu_vertex_layout_builder::add_attribute(std::string_view name, gpu_vertex_attribute_type type, bool normalized)
{
    if(attributes_.size() == gpu_vertex_layout::max_attribute_count - 1)
    {
        throw std::out_of_range{"too many vertex attributes specified"};
    }

    attributes_.emplace_back(name, type, normalized);

    return *this;
}

gpu_vertex_layout gpu_vertex_layout_builder::build()
{
    gpu_vertex_layout new_layout;
    new_layout.attribute_count_ = attributes_.size();
    for(int i = 0; i < attributes_.size(); ++i)
    {
        new_layout.attributes_[i] = attributes_[i];
    }

    return new_layout;
}

}