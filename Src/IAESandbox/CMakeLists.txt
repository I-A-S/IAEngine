
set(IAESandbox_Sources
    imp/cpp/Main.cpp
    imp/cpp/Game.cpp
    imp/cpp/Map.cpp
    imp/cpp/Ground.cpp
    imp/cpp/Player.cpp
)

add_executable(IAESandbox ${IAESandbox_Sources})

target_include_directories(IAESandbox PRIVATE imp/hpp)

target_link_libraries(IAESandbox PRIVATE IAEngine)
