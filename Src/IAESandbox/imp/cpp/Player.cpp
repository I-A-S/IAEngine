#include <Player.hpp>

#include <IAEngine/Input.hpp>

#include <IACore/File.hpp>

namespace ia::iae::game
{
    Player::Player(IN Engine *engine) : m_engine(engine)
    {
        m_spriteRenderer = AddComponent<SpriteRendererComponent>();
    }

    VOID Player::OnAdded(IN Scene *scene)
    {
        Node::OnAdded(scene);
    }

    VOID Player::OnRemoved()
    {

        Node::OnRemoved();
    }

    VOID Player::Draw()
    {
        Node::Draw();
    }

    VOID Player::Update()
    {
        Node::Update();
    }
} // namespace ia::iae::game