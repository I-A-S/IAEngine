// IAEngine: 2D ECS Game Engine.
// Copyright (C) 2026 IAS (ias@iasoft.dev)
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <iaengine/engine.hpp>

#include <iaengine/providers/input.hpp>
#include <iaengine/components/transform.hpp>

#include <SDL3/SDL.h>

namespace iae
{
  struct PlayerTag
  {
  };

  auto player_input_system(EntityRegistry &registry, f32 delta_time) -> void
  {
    Vec2 axis_input{};

    auto &input = registry.ctx().get<InputProvider>();
    if (input.is_key_active(SDL_SCANCODE_W))
      axis_input.y += delta_time;
    if (input.is_key_active(SDL_SCANCODE_S))
      axis_input.y += -delta_time;
    if (input.is_key_active(SDL_SCANCODE_A))
      axis_input.x += -delta_time;
    if (input.is_key_active(SDL_SCANCODE_D))
      axis_input.x += delta_time;

    auto view = registry.view<PlayerTag>();

    for (auto player : view)
    {
      auto &transform = registry.get<LocalTransformComponent>(player);

      transform.position += Vec3(axis_input, 0.0f);

      registry.emplace<DirtyTransformTag>(player);
    }
  }

  auto main() -> Result<void>
  {
    auto &logger = auxid::get_thread_logger();

    static constexpr u32 WINDOW_WIDTH = 800;
    static constexpr u32 WINDOW_HEIGHT = 600;

    SDL_Window *window{};

    if (!SDL_Init(SDL_INIT_VIDEO))
    {
      logger.error("failed to initialize SDL '%s'", SDL_GetError());
      exit(-1);
    }

    window =
        SDL_CreateWindow("WZEngine Sandbox", WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_VULKAN | SDL_WINDOW_RESIZABLE);

    if (!window)
    {
      logger.error("failed to create SDL window '%s'", SDL_GetError());
      exit(-1);
    }
    SDL_SetWindowRelativeMouseMode(window, true);
    SDL_ShowWindow(window);

    AU_TRY_DISCARD(Engine::instance().initialize());

    logger.info("successfully intiailized the engine");

    const auto player = Engine::instance().create_entity("player");
    Engine::instance().add_component_to_entity<PlayerTag>(player);

    bool running = true;
    f32 delta_time = 0.0f;
    f32 last_frame = 0.0f;
    while (running)
    {
      Engine::instance().process_events();

      if (Engine::instance().get_input_provider().was_key_pressed(SDL_SCANCODE_ESCAPE))
        running = false;

      const auto current_frame = ((f32) SDL_GetTicks()) / 1000.0f;
      delta_time = current_frame - last_frame;
      last_frame = current_frame;

      player_input_system(Engine::instance().get_entity_registry(), delta_time);

      Engine::instance().iterate(delta_time);
    }

    Engine::instance().terminate();

    logger.info("cleanly exited the engine");

    SDL_DestroyWindow(window);

    SDL_Quit();

    return {};
  }
} // namespace iae

int main(int argc, char *argv[])
{
  au::auxid::MainThreadGuard _thread_guard;

  const auto res = iae::main();
  if (!res)
  {
    au::auxid::get_thread_logger().error("%s", res.error().c_str());
    return -1;
  }

  return 0;
}