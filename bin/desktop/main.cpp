#include "main_window_control_node.hpp"
#include <atelier/scene_tree.hpp>

#include <iostream>
#include <SDL.h>

/**
 * Launch the main game loop
 * @param argc The number of arguments
 * @param argv The list of arguments
 * @return the exit code of the program
 */
int launch_main_loop(int argc, char* argv[]);

/**
 * Entry point of the launcher
 * @param argc The number of arguments passed to this process
 * @param argv The list of arguments passed to this process
 * @return the exit code of the process
 */
int main(int argc, char* argv[])
{
    if(SDL_Init(SDL_INIT_EVERYTHING))
    {
        std::cerr << "Failed to initialize SDL2" << std::endl;
        return 1;
    }

    const int result = launch_main_loop(argc, argv);

    SDL_Quit();

    return result;
}

int launch_main_loop(int argc, char* argv[])
{
    // Here we construct the main scene hierarchy
    at::main_window_control_node main_window;

    // Here we setup the main scene tree
    at::scene_tree tree;
    tree.set_root(&main_window);

    while(main_window.running())
    {
        tree.tick(at::frame_duration{});
    }

    return 0;
}