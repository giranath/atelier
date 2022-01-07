#include "main_window_control_node.hpp"

namespace at
{

SDL_GLContext& main_window_control_node::opengl_context() noexcept
{
    return gl_context_;
}

SDL_Window* main_window_control_node::window() noexcept
{
    return window_;
}

bool main_window_control_node::running() const
{
    return running_;
}

void main_window_control_node::on_ticking(frame_duration dt)
{
    SDL_Event event;
    while(SDL_PollEvent(&event))
    {
        if(event.type == SDL_QUIT)
        {
            running_ = false;
        }
    }
}

void main_window_control_node::on_entering_scene()
{
    window_ = SDL_CreateWindow("Main window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL);
    if(!window_)
    {
        throw std::runtime_error{"failed to create main window"};
    }

    gl_context_ = SDL_GL_CreateContext(window_);
    if(!gl_context_)
    {
        SDL_DestroyWindow(window_);
        throw std::runtime_error{"failed to create OpenGL context"};
    }

    running_ = true;
}

void main_window_control_node::on_left_scene()
{
    SDL_GL_DeleteContext(gl_context_);
    SDL_DestroyWindow(window_);
}

}