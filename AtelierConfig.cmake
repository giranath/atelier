include(CMakeFindDependencyMacro)

if(NOT TARGET Atelier::runtime)
    include("${CMAKE_CURRENT_LIST_DIR}/AtelierTargets.cmake")
endif()