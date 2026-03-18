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

#include <iaengine/providers/input.hpp>

#include <SDL3/SDL_events.h>

namespace iae
{
  auto InputProvider::process_event(const SDL_Event &event) -> void
  {
    if (event.type == SDL_EVENT_KEY_DOWN)
    {
      if (!event.key.repeat)
      {
        m_keys_pressed_this_frame.push_back(event.key.scancode);
        m_keys_held[event.key.scancode] = true;
      }
    }
    else if (event.type == SDL_EVENT_KEY_UP)
    {
      m_keys_held[event.key.scancode] = false;
    }

    // [IATODO]: Mouse, Gamepad
  }
} // namespace iae