#include "scene_node.hpp"
#include "scene_tree.hpp"
#include "scene_node_errors.hpp"

namespace at
{

void scene_node::attach_to(scene_node& parent)
{
    if(parent_)
    {
        throw scene_node_already_attached_error{this};
    }

    // Link this node with its parent and vice-versa
    parent_ = &parent;

    // The parent already have some children attached to it
    if(parent_->last_child_)
    {
        // Insert this node at the end of the children list
        previous_sibling_ = parent_->last_child_;
        parent_->last_child_->next_sibling_ = this;
        parent_->last_child_ = this;
    }
    // This is the first child node of the parent
    else
    {
        parent_->first_child_ = this;
        parent_->last_child_ = this;
    }

    on_attached();

    // If this parent was owned by a scene, notify this hierarchy that it's entering a scene
    if(parent_->owning_scene_)
    {
        propagate_enter_scene(parent_->owning_scene_);
    }
}

void scene_node::attach_before(scene_node& sibling)
{
    if(parent_)
    {
        throw scene_node_already_attached_error{this};
    }

    parent_ = sibling.parent_;
    next_sibling_ = &sibling;
    previous_sibling_ = sibling.previous_sibling_;

    if(previous_sibling_)
    {
        previous_sibling_->next_sibling_ = this;
    }

    sibling.previous_sibling_ = this;

    on_attached();

    // If this parent was owned by a scene, notify this hierarchy that it's entering a scene
    if(parent_->owning_scene_)
    {
        propagate_enter_scene(parent_->owning_scene_);
    }
}

void scene_node::attach_after(scene_node& sibling)
{
    if(parent_)
    {
        throw scene_node_already_attached_error{this};
    }

    parent_ = sibling.parent_;
    previous_sibling_ = &sibling;
    next_sibling_ = sibling.next_sibling_;

    if(next_sibling_)
    {
        next_sibling_->previous_sibling_ = this;
    }

    sibling.next_sibling_ = this;

    on_attached();

    // If this parent was owned by a scene, notify this hierarchy that it's entering a scene
    if(parent_->owning_scene_)
    {
        propagate_enter_scene(parent_->owning_scene_);
    }
}

bool scene_node::try_attach_to(scene_node& parent)
{
    try
    {
        attach_to(parent);
        return true;
    }
    catch(const scene_node_error&)
    {
        return false;
    }
}

bool scene_node::try_attach_before(scene_node& sibling)
{
    try
    {
        attach_before(sibling);
        return true;
    }
    catch(const scene_node_error&)
    {
        return false;
    }
}

bool scene_node::try_attach_after(scene_node& sibling)
{
    try
    {
        attach_after(sibling);
        return true;
    }
    catch(const scene_node_error&)
    {
        return false;
    }
}

void scene_node::detach_from_parent()
{
    if(owning_scene_)
    {
        propagate_leave_scene();
    }

    if(parent_)
    {
        on_detaching();

        if(parent_->first_child_ == this)
        {
            parent_->first_child_ = next_sibling_;
        }

        if(parent_->last_child_ == this)
        {
            parent_->last_child_ = previous_sibling_;
        }

        if(previous_sibling_)
        {
            previous_sibling_->next_sibling_ = next_sibling_;
        }

        if(next_sibling_)
        {
            next_sibling_->previous_sibling_ = previous_sibling_;
        }

        parent_ = nullptr;
        next_sibling_ = nullptr;
        previous_sibling_ = nullptr;

        on_detached();
    }
}

bool scene_node::empty() const noexcept
{
    return first_child_ == nullptr;
}

bool scene_node::attached() const noexcept
{
    return parent_ != nullptr;
}

scene_node* scene_node::parent() noexcept
{
    return parent_;
}

const scene_node* scene_node::parent() const noexcept
{
    return parent_;
}

scene_node* scene_node::first_child() noexcept
{
    return first_child_;
}

const scene_node* scene_node::first_child() const noexcept
{
    return first_child_;
}

scene_node* scene_node::last_child() noexcept
{
    return last_child_;
}

const scene_node* scene_node::last_child() const noexcept
{
    return last_child_;
}

scene_node* scene_node::next_sibling() noexcept
{
    return next_sibling_;
}

const scene_node* scene_node::next_sibling() const noexcept
{
    return next_sibling_;
}

scene_node* scene_node::previous_sibling() noexcept
{
    return previous_sibling_;
}

const scene_node* scene_node::previous_sibling() const noexcept
{
    return previous_sibling_;
}

scene_node* scene_node::root() noexcept
{
    if(owning_scene_)
    {
        return owning_scene_->root();
    }
    else if(parent_)
    {
        return parent_->root();
    }
    else
    {
        return this;
    }
}

const scene_node* scene_node::root() const noexcept
{
    if(owning_scene_)
    {
        return owning_scene_->root();
    }
    else if(parent_)
    {
        return parent_->root();
    }
    else
    {
        return this;
    }
}

scene_tree* scene_node::scene() noexcept
{
    return owning_scene_;
}

const scene_tree* scene_node::scene() const noexcept
{
    return owning_scene_;
}

scene_node::children_range scene_node::children() noexcept
{
    return children_range{first_child_};
}

void scene_node::propagate_tick(frame_duration dt)
{
    on_ticking(dt);

    for(scene_node& child : children())
    {
        child.propagate_tick(dt);
    }

    on_ticked(dt);
}

void scene_node::propagate_enter_scene(scene_tree* new_scene)
{
    on_entering_scene();

    for(scene_node& child : children())
    {
        child.propagate_enter_scene(new_scene);
    }

    owning_scene_ = new_scene;

    on_entered_scene();
}

void scene_node::propagate_leave_scene()
{
    on_leaving_scene();

    for(scene_node& child : children())
    {
        child.propagate_leave_scene();
    }

    owning_scene_ = nullptr;

    on_left_scene();
}

void scene_node::on_ticking(frame_duration)
{
    // Intentionally a NO-OP
}

void scene_node::on_ticked(frame_duration)
{
    // Intentionally a NO-OP
}

void scene_node::on_attached()
{
    // Intentionally a NO-OP
}

void scene_node::on_detaching()
{
    // Intentionally a NO-OP
}

void scene_node::on_detached()
{
    // Intentionally a NO-OP
}

void scene_node::on_entering_scene()
{
    // Intentionally a NO-OP
}

void scene_node::on_entered_scene()
{
    // Intentionally a NO-OP
}

void scene_node::on_leaving_scene()
{
    // Intentionally a NO-OP
}

void scene_node::on_left_scene()
{
    // Intentionally a NO-OP
}

}