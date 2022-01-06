#include "scene_node_errors.hpp"

namespace at
{

scene_node_error::scene_node_error(scene_node* node) noexcept
: node_{node}
{

}

scene_node* scene_node_error::node() noexcept
{
    return node_;
}

const scene_node* scene_node_error::node() const noexcept
{
    return node_;
}

scene_node_already_attached_error::scene_node_already_attached_error(scene_node* node) noexcept
: scene_node_error{node}
{

}

const char* scene_node_already_attached_error::what() const noexcept
{
    return "node already attached";
}


}