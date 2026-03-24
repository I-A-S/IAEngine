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
  class RenderProvider
  {
public:
    auto resize(i32 width, i32 height, bool force_resize = false) -> void;

public:
    auto create_texture(const u8 *rgba, i32 width, i32 height) -> Result<ResourceHandle>;

private:
    i32 m_width{};
    i32 m_height{};
    void *m_imdraw_data{};
    void *m_device_handle{};
    void *m_cmdbuffer_handle{};
    void *m_renderpass_handle{};

private:
    auto begin_frame() -> void;
    auto end_frame() -> void;

    auto initialize() -> Result<void>;
    auto terminate() -> void;

    auto process_event(const SDL_Event &event) -> void;

    friend class Engine;
  };
} // namespace iae