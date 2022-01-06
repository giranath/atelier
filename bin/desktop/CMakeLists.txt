add_executable(desktop_launcher
        main.cpp)

target_link_libraries(desktop_launcher
        PRIVATE runtime)

set_target_properties(desktop_launcher PROPERTIES
        OUTPUT_NAME AtelierGame)