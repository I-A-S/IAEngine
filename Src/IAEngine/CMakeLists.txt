
set(IAEngine_Sources
    imp/cpp/IAEngine.cpp
)

add_library(IAEngine STATIC ${IAEngine_Sources})

target_include_directories(IAEngine PUBLIC inc/)
target_include_directories(IAEngine PRIVATE imp/hpp)

target_link_libraries(IAEngine PUBLIC IACore)
