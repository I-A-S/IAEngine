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

#include <systems/transform.hpp>

#include <SDL3/SDL_events.h>

namespace iae
{
  struct DebugInfoComponent
  {
    char name[256];
  };
} // namespace iae

namespace iae
{
  TransformSystem g_transform_system{};

  auto Engine::initialize() -> Result<void>
  {
    AU_TRY_DISCARD(m_display_provider.initialize());
    AU_TRY_DISCARD(m_input_provider.initialize());
    AU_TRY_DISCARD(m_render_provider.initialize());
    AU_TRY_DISCARD(m_asset_provider.initialize());

    return {};
  }

  auto Engine::terminate() -> void
  {
    m_asset_provider.terminate();
    m_render_provider.terminate();
    m_input_provider.terminate();
    m_display_provider.terminate();
  }

  auto Engine::resize(i32 width, i32 height) -> void
  {
    m_display_provider.resize(width, height);
    m_render_provider.resize(width, height);
  }

  auto Engine::iterate(f32 delta_time) -> void
  {
    g_transform_system.update(m_entity_registry);

    m_render_provider.begin_frame();

    m_render_provider.end_frame();

    // auto view = m_entity_registry.view<DebugInfoComponent, WorldTransformComponent>();
    // for (auto entity : view)
    //{
    //   const auto &t = view.get<WorldTransformComponent>(entity);
    //   auxid::get_thread_logger().info("Entity (%s): Pos: (%.2f, %.2f, %.2f)",
    //   view.get<DebugInfoComponent>(entity).name,
    //                                   t.position.x, t.position.y, t.position.z);
    // }
  }

  auto Engine::process_events() -> void
  {
    m_input_provider.reset_for_frame();

    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
      if (event.type == SDL_EVENT_QUIT)
      {
        return;
      }

      m_display_provider.process_event(event);
      m_input_provider.process_event(event);
      m_asset_provider.process_event(event);
      m_render_provider.process_event(event);
    }
  }
} // namespace iae

namespace iae
{
  auto Engine::create_entity(String debug_name) -> EntityID
  {
    DebugInfoComponent dbg_info{};
    if (debug_name.empty())
      memcpy(dbg_info.name, "<not_set>", 10);
    else
    {
      const auto t = std::min(sizeof(dbg_info.name) - 1, debug_name.length());
      memcpy(dbg_info.name, debug_name.c_str(), t);
      dbg_info.name[t] = '\0';
    }

    const auto entity = m_entity_registry.create();
    add_component_to_entity<HierarchyComponent>(entity);
    add_component_to_entity<LocalTransformComponent>(entity);
    add_component_to_entity<WorldTransformComponent>(entity);
    add_component_to_entity<DebugInfoComponent>(entity, dbg_info);

    return entity;
  }

  auto Engine::shift_subtree_depth(EntityID entity, int32_t depth_delta) -> void
  {
    if (depth_delta == 0)
      return;

    auto &h = m_entity_registry.get<HierarchyComponent>(entity);
    h.depth += depth_delta;

    EntityID current_child = h.first_child;
    while (current_child != NULL_ENTITY)
    {
      shift_subtree_depth(current_child, depth_delta);
      current_child = m_entity_registry.get<HierarchyComponent>(current_child).next_sibling;
    }
  }

  auto Engine::attach_entity_to_parent(EntityID entity, EntityID parent) -> void
  {
    deatach_entity_from_parent(entity);

    auto &parent_h = m_entity_registry.get<HierarchyComponent>(parent);
    auto &child_h = m_entity_registry.get<HierarchyComponent>(entity);

    child_h.parent = parent;
    child_h.next_sibling = parent_h.first_child;
    child_h.prev_sibling = NULL_ENTITY;

    if (parent_h.first_child != NULL_ENTITY)
    {
      m_entity_registry.get<HierarchyComponent>(parent_h.first_child).prev_sibling = entity;
    }
    parent_h.first_child = entity;

    int32_t new_depth = parent_h.depth + 1;
    shift_subtree_depth(entity, new_depth);

    m_entity_registry.emplace_or_replace<DirtyTransformTag>(entity);
    m_entity_registry.ctx().emplace<HierarchyChangedTag>();
  }

  auto Engine::deatach_entity_from_parent(EntityID entity) -> void
  {
    auto &h = m_entity_registry.get<HierarchyComponent>(entity);
    if (h.parent == NULL_ENTITY)
      return;

    auto &parent_h = m_entity_registry.get<HierarchyComponent>(h.parent);

    if (h.prev_sibling != NULL_ENTITY)
    {
      m_entity_registry.get<HierarchyComponent>(h.prev_sibling).next_sibling = h.next_sibling;
    }
    else
    {
      parent_h.first_child = h.next_sibling;
    }
    if (h.next_sibling != NULL_ENTITY)
    {
      m_entity_registry.get<HierarchyComponent>(h.next_sibling).prev_sibling = h.prev_sibling;
    }

    h.parent = NULL_ENTITY;
    h.next_sibling = NULL_ENTITY;
    h.prev_sibling = NULL_ENTITY;

    int32_t depth_delta = 0 - h.depth;
    shift_subtree_depth(entity, depth_delta);

    m_entity_registry.emplace_or_replace<DirtyTransformTag>(entity);
    m_entity_registry.ctx().emplace<HierarchyChangedTag>();
  }
} // namespace iae