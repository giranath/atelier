#ifndef ATELIER_RUNTIME_SCENE_NODE_HPP
#define ATELIER_RUNTIME_SCENE_NODE_HPP

#include "runtime_export.hpp"
#include <vector>
#include <stdexcept>

namespace at
{

class scene;

/**
 * Base class every nodes in a scene must implement
 */
class ATELIER_RUNTIME_EXPORT scene_node
{
    friend scene;

    // The scene where this node exist
    scene* owning_scene_;

    // Hierarchy related properties
    scene_node* parent_ = nullptr;
    scene_node* next_sibling_ = nullptr;
    scene_node* previous_sibling_ = nullptr;
    scene_node* first_child_ = nullptr;
    scene_node* last_child_ = nullptr;

public:
    /**
     * Initializes an empty node
     */
    scene_node() = default;

    /**
     * Attach this node to a parent
     * @param parent The parent node to attach to
     */
    void attach_to(scene_node& parent);

    /**
     * Attach this node as the previous sibling of a node
     * @param sibling The node that will be the next sibling
     */
    void attach_before(scene_node& sibling);

    /**
     * Attach this node as the next sibling of a node
     * @param sibling The node that will be the previous sibling
     */
    void attach_after(scene_node& sibling);

    /**
     * Attach this node to a parent
     * @param parent The parent node to attach to
     * @return true when the node is correctly attached or false if the node could not be attached
     */
    bool try_attach_to(scene_node& parent);

    /**
     * Attach this node as the previous sibling of a node
     * @param sibling The node that will be the next sibling
     * @return true when the node is correctly attached or false if the node could not be attached
     */
    bool try_attach_before(scene_node& sibling);

    /**
     * Attach this node as the next sibling of a node
     * @param sibling The node that will be the previous sibling
     * @return true when the node is correctly attached or false if the node could not be attached
     */
    bool try_attach_after(scene_node& sibling);

    /**
     * Detach this node from its parent
     * @note Will detach all the hierarchy under this node
     */
    void detach_from_parent();

    /**
     * Check if this node has children
     * @return true when the node has no children or false otherwise
     */
    [[nodiscard]] bool empty() const noexcept;

    /**
     * Check if this node is attached to another node
     * @return true when this node has a parent node
     */
    [[nodiscard]] bool attached() const noexcept;

    /**
     * Returns the parent node of this node
     * @return The parent node of this node
     */
    [[nodiscard]] scene_node* parent() noexcept;

    /**
     * Returns the parent node of this node
     * @return The parent node of this node
     */
    [[nodiscard]] const scene_node* parent() const noexcept;

    /**
     * Returns the first child node of this node
     * @return The first child node of this node
     */
    [[nodiscard]] scene_node* first_child() noexcept;

    /**
     * Returns the first child node of this node
     * @return The first child node of this node
     */
    [[nodiscard]] const scene_node* first_child() const noexcept;

    /**
     * Returns the last child node of this node
     * @return The last child node of this node
     */
    [[nodiscard]] scene_node* last_child() noexcept;

    /**
     * Returns the last child node of this node
     * @return The last child node of this node
     */
    [[nodiscard]] const scene_node* last_child() const noexcept;

    /**
     * Returns the next sibling node of this node
     * @return The next sibling node of this node
     */
    [[nodiscard]] scene_node* next_sibling() noexcept;

    /**
     * Returns the next sibling node of this node
     * @return The next sibling node of this node
     */
    [[nodiscard]] const scene_node* next_sibling() const noexcept;

    /**
     * Returns the previous sibling node of this node
     * @return The previous sibling node of this node
     */
    [[nodiscard]] scene_node* previous_sibling() noexcept;

    /**
     * Returns the previous sibling node of this node
     * @return The previous sibling node of this node
     */
    [[nodiscard]] const scene_node* previous_sibling() const noexcept;

    /**
     * Returns the root node of the hierarchy this node is in
     * @return The root node of this node hierarchy
     */
    [[nodiscard]] scene_node* root() noexcept;

    /**
     * Returns the root node of the hierarchy this node is in
     * @return The root node of this node hierarchy
     */
    [[nodiscard]] const scene_node* root() const noexcept;

private:
    /**
     * Propagate the tick event on all the nodes under this node
     */
    void propagate_tick();

    /**
     * Propagate the enter scene event on all nodes under this node
     * @param new_scene The new scene where this node is entering
     */
    void propagate_enter_scene(scene* new_scene);

    /**
     * Propagate the leave scene event on all nodes under this node
     */
    void propagate_leave_scene();

protected:
    /**
     * Called when this node is ticking
     * @note At this point, children have not started ticking
     */
    virtual void on_ticking();

    /**
     * Called when this node is ticking
     * @note At this point, children have finished ticking
     */
    virtual void on_ticked();

    /**
     * Called after this node has attached itself to a new parent
     */
    virtual void on_attached();

    /**
     * Called before this node is being detached from its parent
     * @note At this point, the node is still attached
     */
    virtual void on_detaching();

    /**
     * Called after this node has been detached from its parent
     * @note At this point, the node is fully detached
     */
    virtual void on_detached();

    /**
     * Called before this node enters a scene
     * @note At this point, the node is not inside the scene yet
     */
    virtual void on_entering_scene();

    /**
     * Called after this node enters a scene
     * @note At this point, the node and all its children are inside the scene
     */
    virtual void on_entered_scene();

    /**
     * Called before this node leaves a scene
     * @note At this point, the node is still inside the scene and no children have been notified of this event yet
     */
    virtual void on_leaving_scene();

    /**
     * Called after this node has left a scene
     * @note At this point, the node and all its children are no longer inside the scene
     */
    virtual void on_left_scene();
};

}

#endif
