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
        if (!m_isEmitting)
            return;

        for (auto &s : m_sprites)
            s->Draw();
    }

    VOID ParticleEmitterComponent::Update()
    {
        if (!m_isEmitting)
            return;

        for (auto &s : m_sprites)
            s->Update();

        m_timeline += Time::GetFrameDeltaTime();
        if (m_timeline >= m_lifeTime.GetValue())
        {
            m_timeline = 0;
            m_isEmitting = false;
        }
    }
} // namespace ia::iae