set(SRC_FILES
    cpp/engine.cpp

    cpp/systems/transform.cpp

    cpp/providers/asset.cpp
    cpp/providers/input.cpp
    cpp/providers/render.cpp
    cpp/providers/display.cpp

        cpp/systems/texture_renderer.cpp
)

add_library(IAEngine STATIC ${SRC_FILES})

target_include_directories(IAEngine PUBLIC
    $<BUILD_INTERFACE:${IAEngine_ROOT}/include>
    $<INSTALL_INTERFACE:include>
)
target_include_directories(IAEngine PRIVATE hpp)

target_link_libraries(IAEngine PUBLIC 
    libauxid
    glm::glm
    EnTT::EnTT
    ImGui_Base
)

target_link_libraries(IAEngine PRIVATE
    STB_CMake
    SDL3::SDL3
    ImGui_SDL3_GPU
)

target_compile_options(IAEngine PRIVATE
    "-fno-exceptions"
)
