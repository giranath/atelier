#include "desktop_application.hpp"
#include <iostream>

void desktop_application::on_initializing()
{
    if(SDL_Init(SDL_INIT_EVERYTHING))
    {
        std::cerr << "Failed to initialize SDL2" << std::endl;
        throw std::runtime_error{"failed to initialize SDL2"};
    }
}

void desktop_application::on_terminated()
{
    SDL_Quit();
}

std::unique_ptr<at::gpu_device> desktop_application::make_gpu_device()
{
    return nullptr;
}