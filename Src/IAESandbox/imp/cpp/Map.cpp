#include <Map.hpp>

namespace ia::iae::game
{
    TiledMap::TiledMap(IN Engine *engine) : m_engine(engine)
    {
        m_musicEmitter = AddComponent<SoundEmitterComponent>();
        m_atlasRenderer = AddComponent<AtlasRendererComponent>();
    }

    VOID TiledMap::OnAdded(IN Scene *scene)
    {
        Node::OnAdded(scene);
    }

    VOID TiledMap::OnRemoved()
    {
        Node::OnRemoved();
    }

    VOID TiledMap::Draw()
    {
        Node::Draw();
    }

    VOID TiledMap::Update()
    {
        Node::Update();
    }
} // namespace ia::iae::game