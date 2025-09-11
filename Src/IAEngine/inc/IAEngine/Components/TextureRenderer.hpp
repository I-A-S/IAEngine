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

#include <IAEngine/Components/Component.hpp>
#include <IAEngine/Texture.hpp>

namespace ia::iae
{
    class TextureRendererComponent : public IComponent
    {
      public:
        TextureRendererComponent(IN Node *node);

        RefPtr<iae::Texture> &Texture()
        {
            return m_texture;
        }

        iam::Vec3f &Position()
        {
            return m_position;
        }

      public:
        VOID Draw();
        VOID Update();

      private:
        iam::Vec3f m_position;
        RefPtr<iae::Texture> m_texture;
    };
} // namespace ia::iae