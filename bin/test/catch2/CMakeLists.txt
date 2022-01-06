add_library(catch2 INTERFACE)

target_include_directories(catch2
        INTERFACE include)

add_library(catch2::catch2 ALIAS catch2)