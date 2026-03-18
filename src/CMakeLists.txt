set(SRC_FILES
    cpp/engine.cpp

    cpp/systems/transform.cpp

    cpp/providers/asset.cpp
    cpp/providers/input.cpp
    cpp/providers/render.cpp
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
)

target_link_libraries(IAEngine PRIVATE
    STB_CMake
    SDL3::SDL3
)

target_compile_options(IAEngine PRIVATE
    "-fno-exceptions"
)
