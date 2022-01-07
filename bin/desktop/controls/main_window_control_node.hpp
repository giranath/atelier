#ifndef ATELIER_MAIN_WINDOW_CONTROL_NODE_HPP
#define ATELIER_MAIN_WINDOW_CONTROL_NODE_HPP

#include <atelier/control_node.hpp>
#include <SDL.h>

namespace at
{

class desktop_application;

/**
 * Control node responsible to hold the main window of the application
 * It will also hold the OpenGL context associated with the window
 */
class main_window_control_node final : public at::control_node
{
    desktop_application* app_ = nullptr;
public:
    main_window_control_node() = default;
    main_window_control_node(desktop_application* application);

protected:
};

}

#endif
