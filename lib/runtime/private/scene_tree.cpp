#include "scene_tree.hpp"
#include "scene_node.hpp"

namespace at
{

scene_tree::scene_tree()
: root_{nullptr}
{

}

scene_tree::~scene_tree()
{
    if(root_)
    {
        root_->propagate_leave_scene();
    }
}

scene_tree::scene_tree(scene_tree&& other) noexcept
: root_{std::exchange(other.root_, nullptr)}
{
}

scene_tree& scene_tree::operator=(scene_tree&& other) noexcept
{
    if(&other != this)
    {
        set_root(std::exchange(other.root_, nullptr));
    }

    return *this;
}

void scene_tree::set_root(scene_node* new_root)
{
    if(root_)
    {
        root_->propagate_leave_scene();
    }

    root_ = new_root;

    if(root_)
    {
        root_->propagate_enter_scene(this);
    }
}

scene_node* scene_tree::root() noexcept
{
    return root_;
}

const scene_node* scene_tree::root() const noexcept
{
    return root_;
}

bool scene_tree::empty() const noexcept
{
    return root_ == nullptr;
}

void scene_tree::clear()
{
    set_root(nullptr);
}

void scene_tree::tick(frame_duration dt)
{
    if(root_)
    {
        root_->propagate_tick(dt);
    }
}

}