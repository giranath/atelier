#include <atelier/scene_node.hpp>
#include <atelier/scene_node_errors.hpp>
#include <catch.hpp>

TEST_CASE("scene nodes can be detached", "[scene_node")
{
    at::scene_node root_node;
    at::scene_node child_node;
    child_node.attach_to(root_node);

    REQUIRE_FALSE(root_node.empty());
    REQUIRE(child_node.parent() == &root_node);

    child_node.detach_from_parent();
    REQUIRE(root_node.empty());
    REQUIRE(child_node.parent() == nullptr);
}

TEST_CASE("scene nodes can be attached", "[scene_node]")
{
    at::scene_node root_node;

    REQUIRE(root_node.parent() == nullptr);
    REQUIRE(root_node.empty());

    SECTION("to an empty root node correctly update node hierarchy")
    {
        at::scene_node child_node;
        REQUIRE(child_node.parent() == nullptr);
        REQUIRE(child_node.empty());

        child_node.attach_to(root_node);

        REQUIRE(root_node.parent() == nullptr);
        REQUIRE_FALSE(root_node.empty());
        REQUIRE(child_node.parent() == &root_node);
        REQUIRE(child_node.empty());
    }

    SECTION("to an existing hierarchy correctly update it")
    {
        at::scene_node child_node;
        REQUIRE(child_node.parent() == nullptr);
        REQUIRE(child_node.empty());

        child_node.attach_to(root_node);

        SECTION("trying to reattach child node will throw an exception")
        {
            at::scene_node new_root;

            REQUIRE_THROWS_AS(child_node.attach_to(new_root), at::scene_node_already_attached_error);
        }

        SECTION("attaching as sibling will add another child to the root node and keep existing child node unchanged")
        {
            at::scene_node sibling_node;
            REQUIRE(sibling_node.parent() == nullptr);
            REQUIRE(sibling_node.empty());

            sibling_node.attach_to(root_node);

            REQUIRE_FALSE(root_node.empty());
            REQUIRE(child_node.parent() == &root_node);
            REQUIRE(sibling_node.parent() == &root_node);
            REQUIRE(child_node.next_sibling() == &sibling_node);
            REQUIRE(sibling_node.previous_sibling() == &child_node);
            REQUIRE(sibling_node.empty());
            REQUIRE(child_node.empty());
        }

        SECTION("attaching as child will add another child to the existing child node")
        {
            at::scene_node subchild_node;
            REQUIRE(subchild_node.parent() == nullptr);
            REQUIRE(subchild_node.empty());

            subchild_node.attach_to(child_node);

            REQUIRE_FALSE(root_node.empty());
            REQUIRE(child_node.parent() == &root_node);
            REQUIRE(subchild_node.parent() == &child_node);
            REQUIRE(child_node.next_sibling() == nullptr);
            REQUIRE(subchild_node.previous_sibling() == nullptr);
            REQUIRE(subchild_node.empty());
            REQUIRE_FALSE(child_node.empty());
        }
    }
}