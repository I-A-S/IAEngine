#include <IAEngine/Components/AtlasRenderer.hpp>

#include <IAEngine/Nodes/Node.hpp>

namespace ia::iae
{
    AtlasRendererComponent::AtlasRendererComponent(IN Node *node) : IComponent(node)
    {
    }

    Handle AtlasRendererComponent::AddTexture(IN RefPtr<Texture> texture)
    {
        m_textures.pushBack(texture);
        return m_textures.size() - 1;
    }

    VOID AtlasRendererComponent::SetGrid(IN CONST TileGrid &grid)
    {
        m_tileGrid = grid;
        m_tileGrid.m_tileTextures.resize(grid.TileCountX * grid.TileCountY);
        for (auto &t : m_tileGrid.m_tileTextures)
            t = INVALID_HANDLE;
    }

    VOID AtlasRendererComponent::SetGridTileTexture(IN INT32 x, IN INT32 y, IN Handle textureHandle)
    {
        m_tileGrid.m_tileTextures[x + (y * m_tileGrid.TileCountX)] = textureHandle;
    }

    VOID AtlasRendererComponent::Update()
    {
    }

    VOID AtlasRendererComponent::Draw()
    {
        iam::Vec3f p{m_node->GetPosition().X, m_node->GetPosition().Y, m_node->GetPosition().Z};
        for (INT32 y = 0; y < m_tileGrid.TileCountY; y++)
        {
            for (INT32 x = 0; x < m_tileGrid.TileCountX; x++)
            {
                const auto t = m_tileGrid.m_tileTextures[x + (y * m_tileGrid.TileCountX)];
                if (t != INVALID_HANDLE)
                    m_textures[t]->Draw(p + m_tileGrid.Position, {1.0f, 1.0f, 1.0f}, 0.0f, false, false, {1.0f, 1.0f, 1.0f, 1.0f});
                p.X += m_tileGrid.TileWidth;
            }
            p.X = m_node->GetPosition().X;
            p.Y += m_tileGrid.TileHeight;
        }
    }
} // namespace ia::iae