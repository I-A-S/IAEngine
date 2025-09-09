#pragma once

#include <IAEngine/Components/SoundEmitter.hpp>
#include <IAEngine/Components/SpriteRenderer.hpp>
#include <IAEngine/IAEngine.hpp>

namespace ia::iae::game
{
    class Ground : public Node
    {
      public:
        Ground(IN Engine *engine);

        VIRTUAL VOID OnAdded(IN Scene *scene) OVERRIDE;
        VIRTUAL VOID OnRemoved() OVERRIDE;
        VIRTUAL VOID Draw() OVERRIDE;
        VIRTUAL VOID Update() OVERRIDE;

      private:
        INT32 m_speed{};
        UINT8 m_direction{};

      private:
        Engine *CONST m_engine;
        RefPtr<SpriteRendererComponent> m_spriteRenderer;
    };
} // namespace ia::iae::game