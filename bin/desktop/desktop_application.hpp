#ifndef ATELIER_DESKTOP_APPLICATION_HPP
#define ATELIER_DESKTOP_APPLICATION_HPP

#include <atelier/application.hpp>
#include <atelier/gpu_device.hpp>

#include <SDL.h>

class desktop_application final : public at::application
{
    SDL_Window* main_window_;
    SDL_GLContext opengl_context_;
protected:
    void on_initializing() override final;
    void on_terminated() override final;
    std::unique_ptr<at::gpu_device> make_gpu_device() override final;
    void setup_scene_root(at::scene_tree& scene) override final;
    void pump_host_events() override final;
};


#endif
