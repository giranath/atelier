#include "scene.hpp"
#include "scene_node.hpp"

namespace at
{

scene::scene()
: root_{nullptr}
{

}

scene::~scene()
{
    if(root_)
    {
        root_->propagate_leave_scene();
    }
}

scene::scene(scene&& other) noexcept
: root_{std::exchange(other.root_, nullptr)}
{
}

scene& scene::operator=(scene&& other) noexcept
{
    if(&other != this)
    {
        set_root(std::exchange(other.root_, nullptr));
    }

    return *this;
}

void scene::set_root(scene_node* new_root)
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

scene_node* scene::root() noexcept
{
    return root_;
}

const scene_node* scene::root() const noexcept
{
    return root_;
}

bool scene::empty() const noexcept
{
    return root_;
}

void scene::clear()
{
    set_root(nullptr);
}

void scene::tick()
{
    if(root_)
    {
        root_->propagate_tick();
    }
}

}