#include <IAEngine/Components/ParticleEmitter.hpp>

namespace ia::iae
{
    ParticleEmitterComponent::ParticleEmitterComponent(IN Node *node) : IComponent(node)
    {
    }

    VOID ParticleEmitterComponent::AddAnimation(IN SpriteRendererComponent::Animation anim)
    {
        const auto spriteRenderer = MakeRefPtr<SpriteRendererComponent>(m_node);
        spriteRenderer->AddAnimation(anim);
        spriteRenderer->BakeAnimations();
        m_sprites.pushBack(spriteRenderer);
    }

    VOID ParticleEmitterComponent::Draw()
    {
        for(auto& s: m_sprites)
            s->Draw();
    }

    VOID ParticleEmitterComponent::Update()
    {
        for(auto& s: m_sprites)
            s->Update();
    }
} // namespace ia::iae