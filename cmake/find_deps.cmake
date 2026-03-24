include(FetchContent)

FetchContent_Declare(
  entt
  GIT_REPOSITORY https://github.com/skypjack/entt
  GIT_TAG        main
  OVERRIDE_FIND_PACKAGE
)

FetchContent_Declare(
  glm
  GIT_REPOSITORY https://github.com/g-truc/glm
  GIT_TAG        master
  OVERRIDE_FIND_PACKAGE
)

FetchContent_Declare(
  SDL
  GIT_REPOSITORY https://github.com/libsdl-org/SDL
  GIT_TAG        main
  OVERRIDE_FIND_PACKAGE
)

FetchContent_Declare(
  STB_CMake
  GIT_REPOSITORY https://github.com/I-A-S/stb-cmake
  GIT_TAG        main
  OVERRIDE_FIND_PACKAGE
)

FetchContent_Declare(
  DearImGui_CMake
  GIT_REPOSITORY https://github.com/I-A-S/imgui-cmake
  GIT_TAG        main
  OVERRIDE_FIND_PACKAGE
)

FetchContent_MakeAvailable(entt glm SDL STB_CMake DearImGui_CMake)
