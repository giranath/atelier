#include "main_window_control_node.hpp"
#include "desktop_application.hpp"

namespace at
{

main_window_control_node::main_window_control_node(desktop_application* application)
: at::control_node()
, app_{application}
{

}

}