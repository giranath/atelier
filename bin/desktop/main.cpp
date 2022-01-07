#include "controls/main_window_control_node.hpp"
#include <atelier/gpu_device.hpp>
#include <atelier/application.hpp>

#include <iostream>
#include <SDL.h>

/**
 * Implementation of the desktop application
 */
class desktop_application final : public at::application
{
    SDL_Window* main_window_;
    SDL_GLContext opengl_context_;
protected:
    void on_initializing() override final
    {
        if(SDL_Init(SDL_INIT_EVERYTHING))
        {
            std::cerr << "Failed to initialize SDL2" << std::endl;
            throw std::runtime_error{"failed to initialize SDL2"};
        }
    }

    void on_initialized() override final
    {

    }

    void on_terminated() override final
    {
        SDL_Quit();
    }

    std::unique_ptr<at::gpu_device> make_gpu_device() override final
    {
        return nullptr;
    }
};

/**
 * Entry point of the launcher
 * @param argc The number of arguments passed to this process
 * @param argv The list of arguments passed to this process
 * @return the exit code of the process
 */
int main(int argc, char* argv[])
{
    return at::launch_application(argc, argv, []() -> std::unique_ptr<at::application>
    {
        return std::make_unique<desktop_application>();
    });

#if 0

    if(SDL_Init(SDL_INIT_EVERYTHING))
    {
        std::cerr << "Failed to initialize SDL2" << std::endl;
        return 1;
    }

    const int result = launch_main_loop(argc, argv);

    SDL_Quit();

    return result;
#endif
}