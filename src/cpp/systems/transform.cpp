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

#include <systems/transform.hpp>

namespace iae
{
  auto TransformSystem::update(EntityRegistry &registry) -> void
  {
    if (registry.ctx().contains<HierarchyChangedTag>())
    {
      registry.sort<HierarchyComponent>([](const auto &lhs, const auto &rhs) { return lhs.depth < rhs.depth; });
      registry.ctx().erase<HierarchyChangedTag>();
    }

    auto view = registry.view<HierarchyComponent, LocalTransformComponent, WorldTransformComponent>();
    view.use<HierarchyComponent>();

    for (const auto entity : view)
    {
      bool is_dirty = registry.any_of<DirtyTransformTag>(entity);

      const auto &h = view.get<HierarchyComponent>(entity);

      if (!is_dirty && h.parent != NULL_ENTITY)
      {
        is_dirty = registry.any_of<DirtyTransformTag>(h.parent);
        if (is_dirty)
        {
          registry.emplace<DirtyTransformTag>(entity);
        }
      }

      if (is_dirty)
      {
        const auto &local = view.get<LocalTransformComponent>(entity);
        auto &world = view.get<WorldTransformComponent>(entity);

        if (h.parent != NULL_ENTITY)
        {
          const auto &parent_world = view.get<WorldTransformComponent>(h.parent);

          world.position = parent_world.position + local.position;
          world.scale = parent_world.scale * local.scale;
          world.rotation = parent_world.rotation + local.rotation;
        }
        else
        {
          world.position = local.position;
          world.scale = local.scale;
          world.rotation = local.rotation;
        }
      }
    }

    registry.clear<DirtyTransformTag>();
  }
} // namespace iae