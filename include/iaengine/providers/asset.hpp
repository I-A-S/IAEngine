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
  class AssetProvider
  {
public:
    auto create_texture_from_file(const char *path) -> Result<ResourceHandle>;
    auto create_texture_from_memory(const void *data, usize data_length) -> Result<ResourceHandle>;
    auto create_texture_from_memory_rgba(const u8 *data, i32 width, i32 height) -> Result<ResourceHandle>;

private:
    auto initialize() -> void;
    auto terminate() -> void;

    auto process_event(const SDL_Event &event) -> void
    {
    }

    friend class Engine;
  };
} // namespace iae