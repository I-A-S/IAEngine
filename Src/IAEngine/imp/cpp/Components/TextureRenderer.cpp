#include <IAEngine/Components/TextureRenderer.hpp>

#include <IAEngine/Nodes/Node.hpp>

namespace ia::iae
{
    TextureRendererComponent::TextureRendererComponent(IN Node *node) : IComponent(node)
    {
    }

    VOID TextureRendererComponent::Update()
    {
        
    }

    VOID TextureRendererComponent::Draw()
    {
        m_texture->Draw(
            m_node->GetPosition() + m_position, m_node->GetScale(),
            m_node->GetRotation().Z, false, false, iam::Vec4f{1.0f, 1.0f, 1.0f, 1.0f});
    }
} // namespace ia::iae