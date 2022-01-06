#include "scene_node_sibling_iterator.hpp"
#include "scene_node.hpp"

namespace at
{

scene_node_sibling_iterator::scene_node_sibling_iterator() noexcept
: node_{nullptr}
{

}

scene_node_sibling_iterator::scene_node_sibling_iterator(scene_node* node) noexcept
: node_{node}
{

}

scene_node* scene_node_sibling_iterator::operator->() noexcept
{
    return node_;
}

scene_node& scene_node_sibling_iterator::operator*() noexcept
{
    return *node_;
}

scene_node_sibling_iterator& scene_node_sibling_iterator::operator++() noexcept
{
    if(node_)
    {
        node_ = node_->next_sibling();
    }

    return *this;
}

scene_node_sibling_iterator scene_node_sibling_iterator::operator++(int) noexcept
{
    scene_node_sibling_iterator tmp{*this};

    ++(*this);

    return tmp;
}

scene_node_sibling_iterator& scene_node_sibling_iterator::operator--() noexcept
{
    if(node_)
    {
        node_ = node_->previous_sibling();
    }

    return *this;
}

scene_node_sibling_iterator scene_node_sibling_iterator::operator--(int) noexcept
{
    scene_node_sibling_iterator tmp{*this};

    --(*this);

    return tmp;
}

bool scene_node_sibling_iterator::operator==(const scene_node_sibling_iterator& other) const noexcept
{
    return node_ == other.node_;
}

bool scene_node_sibling_iterator::operator!=(const scene_node_sibling_iterator& other) const noexcept
{
    return node_ != other.node_;
}

}