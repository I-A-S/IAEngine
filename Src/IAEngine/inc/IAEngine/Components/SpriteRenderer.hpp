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

#include <IAEngine/Components/Component.hpp>
#include <IAEngine/Texture.hpp>

namespace ia::iae
{
    class SpriteRendererComponent : public IComponent
    {
      public:
        struct AnimationKeyFrame
        {
            INT32 Duration{100};
            iam::Vec3f Position{};
            iam::Vec3f Rotation{};
            iam::Vec3f Scale{1.0f, 1.0f, 1.0f};
            iam::Vec4f ColorOverlay{1.0f, 1.0f, 1.0f, 1.0f};
            BOOL ShouldInterpolate{};
            INT32 TextureHandle{INVALID_HANDLE};
        };

        struct Animation
        {
            BOOL ShouldLoop{false};
            Vector<AnimationKeyFrame> Keys;
        };

      public:
        SpriteRendererComponent(IN Node *node);

        Handle AddTexture(IN RefPtr<Texture> texture);
        Handle AddAnimation(IN CONST Animation &animation);
        Handle AddAnimation(IN initializer_list<INT32> frames, IN INT32 frameDuration, IN BOOL shouldLoop);
        Handle AddAnimation(IN INT32 startFrame, IN INT32 endFrame, IN INT32 frameDuration, IN BOOL shouldLoop);

        VOID BakeAnimations();

        VOID SetActiveTexture(IN Handle texture);
        VOID SetActiveAnimation(IN Handle animation);

      public:
        VOID Draw();
        VOID Update();

      private:
        VOID UpdateAnimation();

      private:
        BOOL m_isFlippedV{false};
        BOOL m_isFlippedH{false};
        FLOAT32 m_timelinePosition{};
        Animation m_activeAnimation{};
        Handle m_activeAnimationHandle{INVALID_HANDLE};
        Vector<Animation> m_animations;
        Vector<RefPtr<Texture>> m_textures;
        AnimationKeyFrame m_currentAnimationState{};
        AnimationKeyFrame m_nextAnimationKeyFrame{};
        AnimationKeyFrame m_prevAnimationKeyFrame{};
        INT32 m_prevAnimationKeyFrameIndex{};
    };
} // namespace ia::iae