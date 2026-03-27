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

#include <systems/texture_renderer.hpp>
#include <iaengine/components/transform.hpp>

namespace iae
{
  auto TextureRendererSystem::update(EntityRegistry &registry, RenderProvider &render) -> void
  {
    auto view = registry.view<WorldTransformComponent, TextureComponent>();

    for (const auto entity : view)
    {
      const auto &transform = view.get<WorldTransformComponent>(entity);
      const auto &texture = view.get<TextureComponent>(entity);
      render.draw_quad(transform.position, transform.scale, transform.rotation, texture.handle, texture.color);
    }
  }
}

