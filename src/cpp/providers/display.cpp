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

#include <iaengine/providers/display.hpp>

#include <SDL3/SDL.h>

namespace iae
{
  auto DisplayProvider::resize(i32 width, i32 height) -> void
  {
    m_width = width;
    m_height = height;

    if AU_UNLIKELY (!m_window_handle)
      return;

    SDL_SetWindowSize((SDL_Window *) m_window_handle, m_width, m_height);
  }

  auto DisplayProvider::initialize() -> Result<void>
  {
    SDL_Window *window{};

    if (!SDL_Init(SDL_INIT_VIDEO))
      return fail("failed to initialize SDL '%s'", SDL_GetError());

    window = SDL_CreateWindow("IAEngine", m_width, m_height, SDL_WINDOW_RESIZABLE);

    if (!window)
      return fail("failed to create SDL window '%s'", SDL_GetError());

    SDL_ShowWindow(window);

    m_window_handle = window;

    return {};
  }

  auto DisplayProvider::terminate() -> void
  {
    SDL_DestroyWindow((SDL_Window *) m_window_handle);

    SDL_Quit();
  }

  auto DisplayProvider::process_event(const SDL_Event &event) -> void
  {
  }
} // namespace iae