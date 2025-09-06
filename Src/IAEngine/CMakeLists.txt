
set(IAEngine_Sources
    imp/cpp/IAEngine.cpp
    imp/cpp/Time.cpp
    imp/cpp/Audio.cpp
    imp/cpp/Texture.cpp
    imp/cpp/Input.cpp
    imp/cpp/Scene.cpp
    imp/cpp/Random.cpp
    imp/cpp/Events/Event.cpp
    imp/cpp/Nodes/Transform.cpp
    imp/cpp/Nodes/Node.cpp
    imp/cpp/Components/SpriteRenderer.cpp
    imp/cpp/Components/SoundEmitter.cpp
)

add_library(IAEngine STATIC ${IAEngine_Sources})

target_include_directories(IAEngine PUBLIC inc/)
target_include_directories(IAEngine PRIVATE imp/hpp)

target_link_libraries(IAEngine PUBLIC IACore IAMath ImGui)
target_link_libraries(IAEngine PRIVATE SDL3::SDL3 SDL3_mixer::SDL3_mixer)
