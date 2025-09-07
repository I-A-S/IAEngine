#pragma once

#include <IAEngine/Components/SoundEmitter.hpp>
#include <IAEngine/Components/AtlasRenderer.hpp>
#include <IAEngine/IAEngine.hpp>

namespace ia::iae::game
{
    class TiledMap : public Node
    {
    public:
        TiledMap(IN Engine* engine);

        VIRTUAL VOID OnAdded(IN Scene *scene) OVERRIDE;
        VIRTUAL VOID OnRemoved() OVERRIDE;
        VIRTUAL VOID Draw() OVERRIDE;
        VIRTUAL VOID Update() OVERRIDE;

    private:
        Engine* CONST m_engine;
        RefPtr<SoundEmitterComponent> m_musicEmitter;
        RefPtr<AtlasRendererComponent> m_atlasRenderer;
    };
}