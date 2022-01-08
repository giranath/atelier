#include "desktop_application.hpp"
#include "glad/glad.h"
#include "controls/main_window_control_node.hpp"

#include <atelier/gpu/opengl45_gpu_device.hpp>
#include <atelier/gpu_pipeline_state.hpp>
#include <atelier/gpu_buffer.hpp>
#include <iostream>

namespace at
{

// TODO: Better integrate this to Atelier's logging when it exists
static void APIENTRY on_gl_debug_message(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userparam)
{
    // ignore non-significant error/warning codes
    if(id == 131169 || id == 131185 || id == 131218 || id == 131204) return;

    std::cout << "---------------" << std::endl;
    std::cout << "Debug message (" << id << "): " <<  message << std::endl;

    switch (source)
    {
        case GL_DEBUG_SOURCE_API:             std::cout << "Source: API"; break;
        case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   std::cout << "Source: Window System"; break;
        case GL_DEBUG_SOURCE_SHADER_COMPILER: std::cout << "Source: Shader Compiler"; break;
        case GL_DEBUG_SOURCE_THIRD_PARTY:     std::cout << "Source: Third Party"; break;
        case GL_DEBUG_SOURCE_APPLICATION:     std::cout << "Source: Application"; break;
        case GL_DEBUG_SOURCE_OTHER:           std::cout << "Source: Other"; break;
    } std::cout << std::endl;

    switch (type)
    {
        case GL_DEBUG_TYPE_ERROR:               std::cout << "Type: Error"; break;
        case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: std::cout << "Type: Deprecated Behaviour"; break;
        case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  std::cout << "Type: Undefined Behaviour"; break;
        case GL_DEBUG_TYPE_PORTABILITY:         std::cout << "Type: Portability"; break;
        case GL_DEBUG_TYPE_PERFORMANCE:         std::cout << "Type: Performance"; break;
        case GL_DEBUG_TYPE_MARKER:              std::cout << "Type: Marker"; break;
        case GL_DEBUG_TYPE_PUSH_GROUP:          std::cout << "Type: Push Group"; break;
        case GL_DEBUG_TYPE_POP_GROUP:           std::cout << "Type: Pop Group"; break;
        case GL_DEBUG_TYPE_OTHER:               std::cout << "Type: Other"; break;
    } std::cout << std::endl;

    switch (severity)
    {
        case GL_DEBUG_SEVERITY_HIGH:         std::cout << "Severity: high"; break;
        case GL_DEBUG_SEVERITY_MEDIUM:       std::cout << "Severity: medium"; break;
        case GL_DEBUG_SEVERITY_LOW:          std::cout << "Severity: low"; break;
        case GL_DEBUG_SEVERITY_NOTIFICATION: std::cout << "Severity: notification"; break;
    } std::cout << std::endl;
    std::cout << std::endl;
}

void desktop_application::on_initializing()
{
    if (SDL_Init(SDL_INIT_EVERYTHING))
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

std::unique_ptr<gpu_device> desktop_application::make_gpu_device()
{
    // NOTE: Here we must create the main window with its OpenGL context to be able to create the gpu device for this application

    // Make sure we create an OpenGL 4.5 core profile
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    main_window_ = SDL_CreateWindow("Atelier", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600,
                                    SDL_WINDOW_OPENGL);
    if (!main_window_)
    {
        throw std::runtime_error{"failed to create window"};
    }

    opengl_context_ = SDL_GL_CreateContext(main_window_);
    if (!opengl_context_)
    {
        SDL_DestroyWindow(main_window_);
        throw std::runtime_error{"failed to create OpenGL context"};
    }

    SDL_GL_MakeCurrent(main_window_, opengl_context_);

    if (gladLoadGLLoader(SDL_GL_GetProcAddress) == 0)
    {
        SDL_GL_DeleteContext(opengl_context_);
        SDL_DestroyWindow(main_window_);

        throw std::runtime_error{"failed to load OpenGL functions"};
    }

    // Debug output
    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(on_gl_debug_message, nullptr);
    glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);

    return std::make_unique<opengl45_gpu_device>();
}

void desktop_application::setup_scene_root(scene_tree& scene)
{
    main_control_node_ = std::make_unique<main_window_control_node>(this);

    // Set this application as the root node of the scene
    scene.set_root(main_control_node_.get());
}

void desktop_application::pump_host_events()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            request_termination();
        }
    }
}

void desktop_application::present_frame_to_player()
{
    // Present the current swapchain
    SDL_GL_SwapWindow(main_window_);
}

}