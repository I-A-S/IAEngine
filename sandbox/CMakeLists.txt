set(SRC_FILES
    "src/cpp/main.cpp"
)

add_executable(Sandbox ${SRC_FILES})

target_link_libraries(Sandbox PRIVATE
    IAEngine
)
