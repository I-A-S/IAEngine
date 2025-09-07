// IAEngine: 2D Game Engine by IA
// Copyright (C) 2025 IAS (ias@iasoft.dev)
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#pragma once

#include <IAEngine/Base.hpp>

namespace ia::iae
{
    class Engine;

    class Texture
    {
      public:
        Texture(IN Engine* engine);
        ~Texture();

      public:
        VOID Draw(IN CONST iam::Vec3f& position, IN CONST iam::Vec3f& scale, IN FLOAT32 rotation, IN BOOL flipH, IN BOOL flipV, IN CONST iam::Vec4f& colorOverlay) CONST;

      public:
        INT32 GetWidth() CONST
        {
            return m_width;
        }

        INT32 GetHeight() CONST
        {
            return m_height;
        }

      private:
        INT32 m_width;
        INT32 m_height;
        PVOID m_handle{};
        Engine* CONST m_engine;

      private:
        friend class Engine;
        friend class ResourceManager;
    };
} // namespace ia::iae