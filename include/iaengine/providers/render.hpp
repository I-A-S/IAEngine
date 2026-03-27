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

#include "iaengine/color.hpp"

#include <iaengine/math.hpp>

namespace iae
{
  class RenderProvider
  {
    struct RenderState
    {
      bool flip_x{};
      bool flip_y{};
      Vec2 texture_offset{};
      Vec2 camera_position{};
      ResourceHandle sampler{};
      Mat4 projection_matrix{};
    };

  public:
    enum class EBufferType
    {
      Vertex,
      Index,
    };

    struct GeometryVertex
    {
      Vec2 position{};
      Vec2 tex{};
      Vec4 color{};
    };

    struct GeometryResource
    {
      ResourceHandle vertex_buffer{};
      ResourceHandle index_buffer{};
      u32 index_count{};
    };

public:
    auto resize(i32 width, i32 height, bool force_resize = false) -> void;

  public:
    auto set_render_state_sampler_clamp() -> void;
    auto set_render_state_sampler_repeat() -> void;

    inline auto draw_quad(const Vec2 &position, const Vec2 &size, f32 rotation, ResourceHandle texture, const Color &color) -> void;
    inline auto draw_circle(const Vec2 &position, const Vec2 &size, f32 rotation, ResourceHandle texture, const Color &color) -> void;

    auto draw_geometry(const GeometryResource &geometry, const Vec2 &position, const Vec2 &size, f32 rotation, ResourceHandle texture, const Color &color) -> void;

public:
    auto create_texture(const u8 *rgba, i32 width, i32 height) -> Result<ResourceHandle>;
    auto create_device_local_buffer(EBufferType type, u32 size, const u8* data) -> Result<ResourceHandle>;

    auto create_geometry(Span<const GeometryVertex> vertices, Span<const u32> indices) -> Result<GeometryResource>;

private:
    i32 m_width{};
    i32 m_height{};

    void *m_imdraw_data{};
    void *m_device_handle{};
    void *m_cmdbuffer_handle{};
    void *m_renderpass_handle{};

    Vec<ResourceHandle> m_buffers{};
    Vec<ResourceHandle> m_textures{};

    GeometryResource m_geometry_handle_quad{};
    GeometryResource m_geometry_handle_circle{};

    ResourceHandle m_geometry_pipeline_handle{};
    ResourceHandle m_postprocess_pipeline_handle{};

    ResourceHandle m_sampler_handle_clamp{};
    ResourceHandle m_sampler_handle_repeat{};

    RenderState m_render_state{};

private:
    auto begin_frame() -> void;
    auto end_frame() -> void;

    auto initialize() -> Result<void>;
    auto terminate() -> void;

    auto process_event(const SDL_Event &event) -> void;

    friend class Engine;

    private:
    auto create_default_resources() -> Result<void>;
  };

  auto RenderProvider::draw_quad(const Vec2 &position, const Vec2 &size,f32 rotation, ResourceHandle texture, const Color &color)
      -> void
  {
    draw_geometry(m_geometry_handle_quad, position, size, rotation, texture, color);
  }

  auto RenderProvider::draw_circle(const Vec2 &position, const Vec2 &size,f32 rotation, ResourceHandle texture, const Color &color)
      -> void
  {
    draw_geometry(m_geometry_handle_circle, position, size, rotation, texture, color);
  }
} // namespace iae