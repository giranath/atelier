#ifndef ATELIER_SCENE_NODE_SIBLING_ITERATOR_HPP
#define ATELIER_SCENE_NODE_SIBLING_ITERATOR_HPP

#include "runtime_export.hpp"
#include <iterator>

namespace at
{

class scene_node;

/**
 * Iterator on children of a scene_node
 */
class ATELIER_RUNTIME_EXPORT scene_node_sibling_iterator
{
    scene_node* node_;

public:
    using difference_type =	ptrdiff_t;
    using value_type = scene_node;
    using pointer = scene_node*;
    using reference = scene_node&;
    using iterator_category = std::bidirectional_iterator_tag;

    scene_node_sibling_iterator() noexcept;
    scene_node_sibling_iterator(scene_node* node) noexcept;

    scene_node* operator->() noexcept;
    scene_node& operator*() noexcept;

    explicit operator bool() const noexcept;

    scene_node_sibling_iterator& operator++() noexcept;
    scene_node_sibling_iterator operator++(int) noexcept;
    scene_node_sibling_iterator& operator--() noexcept;
    scene_node_sibling_iterator operator--(int) noexcept;

    bool operator==(const scene_node_sibling_iterator& other) const noexcept;
    bool operator!=(const scene_node_sibling_iterator& other) const noexcept;
};

}

#endif
