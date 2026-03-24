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

#include <iaengine/providers/asset.hpp>
#include <iaengine/providers/input.hpp>
#include <iaengine/providers/render.hpp>
#include <iaengine/providers/display.hpp>

namespace iae
{
  class Engine
  {
public:
    static auto instance() -> Engine &
    {
      static Engine s_instance{};
      return s_instance;
    }

public:
    auto initialize() -> Result<void>;
    auto terminate() -> void;

    auto process_events() -> void;
    auto iterate(f32 delta_time) -> void;

    auto resize(i32 width, i32 height) -> void;

public:
    auto create_entity(String debug_name = "") -> EntityID;
    auto attach_entity_to_parent(EntityID entity, EntityID parent) -> void;
    auto deatach_entity_from_parent(EntityID entity) -> void;

    inline auto get_entity_registry() -> EntityRegistry &;

    template<typename _component_type, typename... Args>
    auto add_component_to_entity(EntityID entity, Args... args) -> void;

public:
    auto get_display_provider() -> DisplayProvider &
    {
      return m_display_provider;
    }

    auto get_input_provider() -> InputProvider &
    {
      return m_input_provider;
    }

    auto get_asset_provider() -> AssetProvider &
    {
      return m_asset_provider;
    }

    auto get_render_provider() -> RenderProvider &
    {
      return m_render_provider;
    }

private:
    InputProvider m_input_provider;
    AssetProvider m_asset_provider;
    RenderProvider m_render_provider;
    DisplayProvider m_display_provider;

    EntityRegistry m_entity_registry;

private:
    auto shift_subtree_depth(EntityID entity, int32_t depth_delta) -> void;
  };

  auto Engine::get_entity_registry() -> EntityRegistry &
  {
    return m_entity_registry;
  }

  template<typename _component_type, typename... Args>
  auto Engine::add_component_to_entity(EntityID entity, Args... args) -> void
  {
    m_entity_registry.emplace<_component_type>(entity, args...);
  }
} // namespace iae
