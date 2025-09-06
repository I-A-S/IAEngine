# -----------------------------------------------
#  SDL3
# -----------------------------------------------
set(SDL_TEST_LIBRARY OFF)
set(BUILD_SHARED_LIBS OFF)
add_subdirectory(SDL/)

# -----------------------------------------------
#  SDL Mixer
# -----------------------------------------------
set(SDLMIXER_VENDORED OFF)
add_subdirectory(SDL_Mixer/)

# -----------------------------------------------
#  IMGUI
# -----------------------------------------------
add_library(
    ImGui STATIC

    "imgui/imgui.cpp"
    "imgui/imgui_demo.cpp"
    "imgui/imgui_draw.cpp"
    "imgui/imgui_tables.cpp"
    "imgui/imgui_widgets.cpp"
    "imgui/backends/imgui_impl_sdl3.cpp"
    "imgui/backends/imgui_impl_sdlrenderer3.cpp"
)
target_include_directories(
    ImGui PRIVATE

    "SDL/include"
)
target_include_directories(
    ImGui PUBLIC

    "imgui/"
    "imgui/backends"
)
