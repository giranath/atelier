cmake_minimum_required(VERSION 3.14)

project(atelier
    VERSION 2022.1
    DESCRIPTION "A simple 2D game engine")

set(ATELIER_RELEASE_PHASE "development" CACHE STRING "Determine the release phase of this build")
set_property(CACHE ATELIER_RELEASE_PHASE PROPERTY STRINGS development stable candidate)

find_package(SDL2 REQUIRED)
find_package(glm REQUIRED)

add_subdirectory(lib)
add_subdirectory(bin)

include(CMakePackageConfigHelpers)

install(TARGETS runtime desktop_launcher glad EXPORT AtelierTargets
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        RUNTIME DESTINATION bin
        INCLUDES DESTINATION include)

install(DIRECTORY lib/runtime/public/
        DESTINATION include)

install(EXPORT AtelierTargets
        FILE AtelierTargets.cmake
        NAMESPACE Atelier::
        DESTINATION share/cmake/Atelier)

write_basic_package_version_file("AtelierConfigVersion.cmake"
        VERSION ${atelier_VERSION}
        COMPATIBILITY ExactVersion)

install(FILES "AtelierConfig.cmake" "${CMAKE_CURRENT_BINARY_DIR}/AtelierConfigVersion.cmake"
        DESTINATION share/cmake/Atelier)

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/lib/runtime/exports/public/atelier/runtime_export.hpp"
        DESTINATION include/atelier)

export(EXPORT AtelierTargets NAMESPACE Atelier:: FILE AtelierExport.cmake)