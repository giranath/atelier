include(GenerateExportHeader)

add_library(runtime
    public/atelier/version.hpp
    private/version.cpp
    public/atelier/scene_node.hpp
    private/scene_node.cpp
    )

set_target_properties(runtime PROPERTIES
        DEBUG_POSTFIX d
        OUTPUT_NAME atelier-runtime)

target_compile_features(runtime
    PUBLIC cxx_std_17)

generate_export_header(runtime
    BASE_NAME ATELIER_RUNTIME
    EXPORT_FILE_NAME exports/public/atelier/runtime_export.hpp)

configure_file(cmake/current_version,cmake.hpp exports/private/current_version.hpp @ONLY)

target_include_directories(runtime
    PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/public>
           $<INSTALL_INTERFACE:include>
    PRIVATE private
    PRIVATE public/atelier
    
    # Make sure runtime_export.hpp can be included
    PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/exports/public>
    PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/exports/public/atelier>
    PRIVATE $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/exports/private>
    )

