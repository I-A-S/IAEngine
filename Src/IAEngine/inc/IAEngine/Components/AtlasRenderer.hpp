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
    class AtlasRendererComponent : public IComponent
    {
      public:
        struct TileGrid
        {
            INT32 TileWidth{};
            INT32 TileHeight{};
            INT32 TileCountX{};
            INT32 TileCountY{};

            Vector<Handle> m_tileTextures{};

            friend class AtlasRendererComponent;
        };

      public:
        AtlasRendererComponent(IN Node *node);

      public:
        Handle AddTexture(IN RefPtr<Texture> texture);

        VOID SetGrid(IN CONST TileGrid &grid);
        VOID SetGridTileTexture(IN INT32 x, IN INT32 y, IN Handle textureHandle);

      public:
        VOID Draw();
        VOID Update();

      private:
        TileGrid m_tileGrid{};
        Vector<RefPtr<Texture>> m_textures;
    };
} // namespace ia::iae