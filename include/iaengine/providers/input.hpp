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

#pragma once

#include <iaengine/math.hpp>

namespace iae
{
  class InputProvider
  {
public:
    [[nodiscard]] auto is_key_active(u32 scancode) const -> bool
    {
      return m_keys_held[scancode] && !m_keys_consumed[scancode];
    }

    [[nodiscard]] auto was_key_pressed(u32 scancode) const -> bool
    {
      if (m_keys_consumed[scancode])
      {
        return false;
      }
      return std::find(m_keys_pressed_this_frame.begin(), m_keys_pressed_this_frame.end(), scancode) !=
             m_keys_pressed_this_frame.end();
    }

    auto consume_key(u32 scancode) -> void
    {
      m_keys_consumed[scancode] = true;
    }

    auto consume_all() -> void
    {
      std::fill(std::begin(m_keys_consumed), std::end(m_keys_consumed), true);
    }

    auto reset_for_frame() -> void
    {
      std::fill(std::begin(m_keys_consumed), std::end(m_keys_consumed), false);
      m_keys_pressed_this_frame.clear();
    }

private:
    bool m_keys_held[512] = {false};
    bool m_keys_consumed[512] = {false};
    Vec<u32> m_keys_pressed_this_frame;

    auto initialize() -> void
    {
    }

    auto terminate() -> void
    {
    }

    auto process_event(const SDL_Event &event) -> void;

    friend class Engine;
  };
} // namespace iae