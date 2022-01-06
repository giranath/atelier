#include <atelier/scene_tree.hpp>
#include <atelier/scene_node.hpp>
#include <catch.hpp>

TEST_CASE("The root node of a scene may be changed", "[scene_tree]")
{
    at::scene_tree scene;
    REQUIRE(scene.root() == nullptr);
    REQUIRE(scene.empty());

    at::scene_node root_node;
    at::scene_node child_node;
    child_node.attach_to(root_node);
    REQUIRE(root_node.scene() == nullptr);
    REQUIRE(child_node.scene() == nullptr);

    scene.set_root(&root_node);

    REQUIRE(scene.root() == &root_node);
    REQUIRE_FALSE(scene.empty());
    REQUIRE(root_node.scene() == &scene);
    REQUIRE(child_node.scene() == &scene);

    at::scene_node subchild;
    REQUIRE(subchild.scene() == nullptr);

    subchild.attach_to(child_node);
    REQUIRE(subchild.scene() == &scene);

    child_node.detach_from_parent();
    REQUIRE(child_node.scene() == nullptr);
    REQUIRE(subchild.scene() == nullptr);

    scene.clear();
    REQUIRE(root_node.scene() == nullptr);
    REQUIRE(scene.empty());
    REQUIRE(scene.root() == nullptr);
}