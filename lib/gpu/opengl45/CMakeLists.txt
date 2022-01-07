include(GenerateExportHeader)

add_library(gpu_opengl45
        private/opengl45_gpu_device.cpp
        public/atelier/gpu/opengl45_gpu_device.hpp
        private/opengl45_gpu_pipeline_state.cpp
        private/opengl45_gpu_pipeline_state.hpp
        private/opengl45_gpu_buffer.hpp
        private/opengl45_gpu_buffer.cpp
        private/opengl45_gpu_texture.hpp
        private/opengl45_gpu_texture.cpp
        private/opengl45_helpers.hpp
        private/opengl45_helpers.cpp
        )

set_target_properties(gpu_opengl45 PROPERTIES
        DEBUG_POSTFIX d
        OUTPUT_NAME atelier-gpu-opengl45)

target_compile_features(gpu_opengl45
        PUBLIC cxx_std_17)

generate_export_header(gpu_opengl45
        BASE_NAME ATELIER_GPU_OPENGL45
        EXPORT_FILE_NAME exports/public/atelier/gpu/opengl45/gpu_opengl45_export.hpp)

target_include_directories(gpu_opengl45
        PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/public>
               $<INSTALL_INTERFACE:include>
        PRIVATE private
        PRIVATE public/atelier/gpu

        # Make sure runtime_export.hpp can be included
        PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/exports/public>
        PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/exports/public/atelier/gpu/opengl45/>
        )

target_link_libraries(gpu_opengl45
        PUBLIC runtime
        PRIVATE glad::glad)