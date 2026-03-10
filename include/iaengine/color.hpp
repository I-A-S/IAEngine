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
  struct Color
  {
    u8 r{255};
    u8 g{255};
    u8 b{255};
    u8 a{255};

    static auto from_normalized(Vec4 v) -> Color
    {
      return Color{
          .r = static_cast<u8>(v.x * 255.0f),
          .g = static_cast<u8>(v.y * 255.0f),
          .b = static_cast<u8>(v.z * 255.0f),
          .a = static_cast<u8>(v.w * 255.0f),
      };
    }

    [[nodiscard]] auto to_normalized() const -> Vec4
    {
      return Vec4(static_cast<f32>(r) / 255.0f, static_cast<f32>(g) / 255.0f, static_cast<f32>(b) / 255.0f,
                  static_cast<f32>(a) / 255.0f);
    }
  };
} // namespace iae
