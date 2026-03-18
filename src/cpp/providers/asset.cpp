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

#include <iaengine/providers/asset.hpp>
#include <iaengine/providers/render.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

namespace iae
{
  auto AssetProvider::initialize() -> void
  {
  }

  auto AssetProvider::terminate() -> void
  {
  }

  auto AssetProvider::create_texture_from_file(const char *path) -> Result<ResourceHandle>
  {
    i32 w, h, nr;
    const auto pixels = stbi_load(path, &w, &h, &nr, STBI_rgb_alpha);

    if (!pixels)
      return fail("failed create a texture from file '%s'.", path);

    const auto result = AU_TRY(create_texture_from_memory_rgba(pixels, w, h));

    stbi_image_free(pixels);

    return result;
  }

  auto AssetProvider::create_texture_from_memory(const void *data, usize data_length) -> Result<ResourceHandle>
  {
    i32 w, h, nr;
    const auto pixels = stbi_load_from_memory((const stbi_uc *) data, data_length, &w, &h, &nr, STBI_rgb_alpha);

    if (!pixels)
      return fail("failed create a texture from memory.");

    const auto result = AU_TRY(create_texture_from_memory_rgba(pixels, w, h));

    stbi_image_free(pixels);

    return result;
  }

  auto AssetProvider::create_texture_from_memory_rgba(const u8 *data, i32 width, i32 height) -> Result<ResourceHandle>
  {
    return Engine::instance().get_render_provider().create_texture(data, width, height);
  }
} // namespace iae