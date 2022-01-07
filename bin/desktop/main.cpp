#include "controls/main_window_control_node.hpp"
#include "desktop_application.hpp"
#include <atelier/application.hpp>
#include <SDL.h>

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
}