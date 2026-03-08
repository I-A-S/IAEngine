add_library(IAEngine STATIC cpp/engine.cpp)

target_include_directories(IAEngine PUBLIC
    $<BUILD_INTERFACE:${IAEngine_ROOT}/include>
    $<INSTALL_INTERFACE:include>
)
target_include_directories(IAEngine PRIVATE hpp)

target_link_libraries(IAEngine PUBLIC libauxid)
target_link_libraries(IAEngine PRIVATE auxid_platform)
