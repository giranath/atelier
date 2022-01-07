add_executable(desktop_launcher
        main.cpp
        controls/main_window_control_node.cpp
        controls/main_window_control_node.hpp)

target_link_libraries(desktop_launcher
        PRIVATE runtime
        PRIVATE SDL2::SDL2
        PRIVATE SDL2::main)

set_target_properties(desktop_launcher PROPERTIES
        OUTPUT_NAME AtelierGame)

# Make sure SDL.DLL is copied alongside game executable
if(WIN32)
    add_custom_command(TARGET desktop_launcher POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_FILE:SDL2::SDL2> $<TARGET_FILE_DIR:desktop_launcher>)
endif()