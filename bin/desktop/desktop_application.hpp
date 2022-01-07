#ifndef ATELIER_DESKTOP_APPLICATION_HPP
#define ATELIER_DESKTOP_APPLICATION_HPP

#include <atelier/application.hpp>
#include <atelier/gpu_device.hpp>

#include <SDL.h>

#include <memory>

namespace at
{

class main_window_control_node;

class desktop_application final : public at::application
{
    std::unique_ptr<main_window_control_node> main_control_node_ = nullptr;
    SDL_Window* main_window_ = nullptr;
    SDL_GLContext opengl_context_ = nullptr;

public:
    desktop_application() = default;

protected:
    void on_initializing() override final;
    void on_terminated() override final;
    std::unique_ptr<gpu_device> make_gpu_device() override final;
    void setup_scene_root(scene_tree& scene) override final;
    void pump_host_events() override final;
};

}

#endif
