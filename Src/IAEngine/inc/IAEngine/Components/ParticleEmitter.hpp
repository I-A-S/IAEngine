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

#include <IAEngine/Components/SpriteRenderer.hpp>

namespace ia::iae
{
    class ParticleEmitterComponent : public IComponent
    {
      public:
        ParticleEmitterComponent(IN Node *node);

        VOID AddAnimation(IN SpriteRendererComponent::Animation anim);

      public:
        CONST INT32 &LifeTime() CONST
        {
            return m_lifeTime;
        }

        CONST INT32 &CreationFrequency() CONST
        {
            return m_creationFrequency;
        }

        CONST Vector<RefPtr<SpriteRendererComponent>> &Sprites() CONST
        {
            return m_sprites;
        }

        INT32 &LifeTime()
        {
            return m_lifeTime;
        }

        INT32 &CreationFrequency()
        {
            return m_creationFrequency;
        }

        Vector<RefPtr<SpriteRendererComponent>> &Sprites()
        {
            return m_sprites;
        }

      public:
        VOID Draw();
        VOID Update();

      private:
        INT32 m_lifeTime{};
        INT32 m_creationFrequency{};
        Vector<RefPtr<SpriteRendererComponent>> m_sprites{};
    };
} // namespace ia::iae