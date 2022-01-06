#ifndef ATELIER_MAIN_WINDOW_CONTROL_NODE_HPP
#define ATELIER_MAIN_WINDOW_CONTROL_NODE_HPP

#include <atelier/control_node.hpp>
#include <SDL.h>

namespace at
{

/**
 * Control node responsible to hold the main window of the application
 * It will also hold the OpenGL context associated with the window
 */
class main_window_control_node final : public at::control_node
{
    SDL_Window* window_;
    SDL_GLContext gl_context_;
    bool running_;

public:
    /**
     * Returns a reference to the OpenGL context managed by this window
     * @return the OpenGL context managed by this window
     */
    SDL_GLContext& opengl_context() noexcept;

    /**
     * Returns a reference to the window managed by this node
     * @return the window managed by this node
     */
    SDL_Window* window() noexcept;

    [[nodiscard]] bool running() const;

protected:
    virtual void on_ticking(frame_duration dt) override final;

    // Create the window and OpenGL context
    virtual void on_entering_scene() override final;

    // Destroy the window and OpenGL context
    virtual void on_left_scene() override final;
};

}

#endif
