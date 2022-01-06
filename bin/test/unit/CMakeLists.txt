add_executable(unit-tests
        main.cpp)

target_link_libraries(unit-tests
        PRIVATE runtime
        PRIVATE catch2::catch2)