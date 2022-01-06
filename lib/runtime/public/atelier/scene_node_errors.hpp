#ifndef ATELIER_RUNTIME_SCENE_NODE_ERRORS_HPP
#define ATELIER_RUNTIME_SCENE_NODE_ERRORS_HPP

#include "runtime_export.hpp"
#include <stdexcept>

namespace at
{

class scene_node;

/**
 * Exception thrown when trying to attach a node that is already attached
 */
class ATELIER_RUNTIME_EXPORT scene_node_error : public std::exception
{
    scene_node* node_;

public:
    explicit scene_node_error(scene_node* node) noexcept;

    [[nodiscard]] scene_node* node() noexcept;
    [[nodiscard]] const scene_node* node() const noexcept;
};

/**
 * Exception thrown when trying to attach a node that is already attached
 */
class ATELIER_RUNTIME_EXPORT scene_node_already_attached_error final: public scene_node_error
{
public:
    explicit scene_node_already_attached_error(scene_node* node) noexcept;

    [[nodiscard]] const char* what() const noexcept final;
};

}

#endif
