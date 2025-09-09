#include <Ground.hpp>

#include <IAEngine/Physics/Physics.hpp>

#include <IACore/File.hpp>

namespace ia::iae::game
{
    extern ResourceManager* g_resourceManager;

    Handle m_id2;

    Ground::Ground(IN Engine *engine) : m_engine(engine)
    {
        m_spriteRenderer = AddComponent<SpriteRendererComponent>();
    }

    VOID Ground::OnAdded(IN Scene *scene)
    {
        Node::OnAdded(scene);

        iae::SpriteRendererComponent::AnimationKeyFrame keyFrame{};
        const auto d = File::ReadToVector("Graphics/red.png");
        keyFrame.Texture = g_resourceManager->CreateTexture(d.data(), d.size());
        keyFrame.Scale = {3.0f, 0.25f, 1.0f};

        m_spriteRenderer->AddAnimation({.ShouldLoop = true, .Keys = {keyFrame}});
        m_spriteRenderer->BakeAnimations();

        m_id2 = Physics::CreateStaticBody({GetPosition().X + 300, GetPosition().Y + 25});
        Physics::AddBoxCollider(m_id2, {600.0f, 50.0f});
    }

    VOID Ground::OnRemoved()
    {

        Node::OnRemoved();
    }

    VOID Ground::Draw()
    {
        Node::Draw();
    }

    VOID Ground::Update()
    {
        Node::Update();
    }
} // namespace ia::iae::game