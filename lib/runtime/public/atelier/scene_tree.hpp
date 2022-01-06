#ifndef ATELIER_RUNTIME_SCENE_TREE_HPP
#define ATELIER_RUNTIME_SCENE_TREE_HPP

#include "runtime_export.hpp"
#include "frame_duration.hpp"

namespace at
{

class scene_node;

/**
 * Represents a hierarchy of active nodes
 */
class ATELIER_RUNTIME_EXPORT scene_tree
{
    scene_node* root_;
public:
    // Copy is disabled
    scene_tree(const scene_tree&) = delete;
    scene_tree& operator=(const scene_tree& other) = delete;

    /**
     * Initializes an empty scene
     */
    scene_tree();

    /**
     * Destroy a scene
     */
    ~scene_tree();

    /**
     * Move a scene into this
     * @param other The other scene to move into this
     */
    scene_tree(scene_tree&& other) noexcept;

    /**
     * Move a scene into this
     * @param other The scene to move into this
     * @return a reference to this
     */
    scene_tree& operator=(scene_tree&& other) noexcept;

    /**
     * Change the root node of this scene
     * @param new_root The new root node
     */
    void set_root(scene_node* new_root);

    /**
     * Get a reference to the root node
     * @return A reference to the root node
     */
    [[nodiscard]] scene_node* root() noexcept;

    /**
     * Get a reference to the root node
     * @return A reference to the root node
     */
    [[nodiscard]] const scene_node* root() const noexcept;

    /**
     * Check if this scene is empty
     * @return true when this scene is empty or false otherwise
     */
    [[nodiscard]] bool empty() const noexcept;

    /**
     * Clear this scene
     * @note This is equivalent to set_root(nullptr)
     */
    void clear();

    /**
     * Tick the scene
     * @param dt Elapsed time since previous tick
     */
    void tick(frame_duration dt);
};

}

#endif
