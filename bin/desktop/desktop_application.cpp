#include "desktop_application.hpp"
#include "glad/glad.h"
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
    SDL_GL_DeleteContext(opengl_context_);
    SDL_DestroyWindow(main_window_);

    SDL_Quit();
}

std::unique_ptr<at::gpu_device> desktop_application::make_gpu_device()
{
    // Make sure we create an OpenGL 4.5 core profile
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    main_window_ = SDL_CreateWindow("Atelier", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL);
    if(!main_window_)
    {
        throw std::runtime_error{"failed to create window"};
    }

    opengl_context_ = SDL_GL_CreateContext(main_window_);
    if(!opengl_context_)
    {
        SDL_DestroyWindow(main_window_);
        throw std::runtime_error{"failed to create OpenGL context"};
    }

    SDL_GL_MakeCurrent(main_window_, opengl_context_);

    if(gladLoadGLLoader(SDL_GL_GetProcAddress) == 0)
    {
        SDL_GL_DeleteContext(opengl_context_);
        SDL_DestroyWindow(main_window_);

        throw std::runtime_error{"failed to load OpenGL functions"};
    }

    // TODO: Create OpenGL 4.5 core gpu device

    return nullptr;
}