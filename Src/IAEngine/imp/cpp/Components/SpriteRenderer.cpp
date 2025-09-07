#include <IAEngine/Components/SpriteRenderer.hpp>

#include <IAEngine/Nodes/Node.hpp>

#include <IAEngine/Time.hpp>

#include <IAMath/Lerp.hpp>

namespace ia::iae
{
    SpriteRendererComponent::SpriteRendererComponent(IN Node *node) : IComponent(node)
    {
    }

    Handle SpriteRendererComponent::AddTexture(IN RefPtr<Texture> texture)
    {
        m_textures.pushBack(texture);
        return m_textures.size() - 1;
    }

    Handle SpriteRendererComponent::AddAnimation(IN CONST Animation &animation)
    {
        IA_RELEASE_ASSERT(!animation.Keys.empty());
        m_animations.pushBack(animation);
        return m_animations.size() - 1;
    }

    Handle SpriteRendererComponent::AddAnimation(IN initializer_list<INT32> frames, IN INT32 frameDuration,
                                                 IN BOOL shouldLoop)
    {
        Animation anim;
        anim.ShouldLoop = shouldLoop;
        for (const auto &idx : frames)
            anim.Keys.pushBack(AnimationKeyFrame{.Duration = frameDuration, .TextureHandle = idx});
        return AddAnimation(anim);
    }

    Handle SpriteRendererComponent::AddAnimation(IN INT32 startFrame, IN INT32 endFrame, IN INT32 frameDuration,
                                                 IN BOOL shouldLoop)
    {
        Animation anim;
        anim.ShouldLoop = shouldLoop;
        for (INT32 i = startFrame; i < endFrame; i++)
            anim.Keys.pushBack(AnimationKeyFrame{.Duration = frameDuration, .TextureHandle = i});
        return AddAnimation(anim);
    }

    VOID SpriteRendererComponent::BakeAnimations()
    {
        for (auto &anim : m_animations)
        {
            auto t = anim.Keys.back();
            t.Duration = 0;
            anim.Keys.pushBack(t);
        }
        if (m_animations.size())
            SetActiveAnimation(0);
        else
            SetActiveTexture(0);
    }

    VOID SpriteRendererComponent::SetActiveTexture(IN Handle texture)
    {
        IA_RELEASE_ASSERT((texture != INVALID_HANDLE) && (texture < m_textures.size()));
        m_currentAnimationState.TextureHandle = texture;
    }

    VOID SpriteRendererComponent::SetActiveAnimation(IN Handle animation)
    {
        if(animation == m_activeAnimationHandle) return;
        IA_RELEASE_ASSERT((animation != INVALID_HANDLE) && (animation < m_animations.size()));
        m_prevAnimationKeyFrameIndex = 0;
        m_activeAnimation = m_animations[animation];
        m_prevAnimationKeyFrame = m_activeAnimation.Keys[m_prevAnimationKeyFrameIndex + 0];
        m_nextAnimationKeyFrame = m_activeAnimation.Keys[m_prevAnimationKeyFrameIndex + 1];
        m_currentAnimationState = m_prevAnimationKeyFrame;
        m_activeAnimationHandle = animation;
    }

    VOID SpriteRendererComponent::Update()
    {
        UpdateAnimation();
    }

    VOID SpriteRendererComponent::Draw()
    {
        const auto &animFrame = m_currentAnimationState;
        if (animFrame.TextureHandle == INVALID_HANDLE)
            return;
        m_textures[animFrame.TextureHandle]->Draw(
            m_node->GetPosition() + animFrame.Position, m_node->GetScale() * animFrame.Scale,
            m_node->GetRotation().Z + animFrame.Rotation.Z, m_isFlippedH, m_isFlippedV, animFrame.ColorOverlay);
    }

    VOID SpriteRendererComponent::UpdateAnimation()
    {
        const auto keyCount = m_activeAnimation.Keys.size();
        if (!keyCount)
            return;

        if (m_currentAnimationState.ShouldInterpolate)
        {
            const auto t = m_timelinePosition / m_prevAnimationKeyFrame.Duration;
#define INTERP_PROPERTY(name)                                                                                          \
    m_currentAnimationState.name = iam::Lerp(m_prevAnimationKeyFrame.name, m_nextAnimationKeyFrame.name, t);

            INTERP_PROPERTY(Position);
            INTERP_PROPERTY(Rotation);
            INTERP_PROPERTY(Scale);
            INTERP_PROPERTY(ColorOverlay);

#undef INTERP_PROPERTY
        }

        m_timelinePosition += Time::GetFrameDeltaTime();
        if (m_timelinePosition >= m_prevAnimationKeyFrame.Duration)
        {
            m_prevAnimationKeyFrameIndex = (m_prevAnimationKeyFrameIndex + 1) % (keyCount - 1);
            if (!m_prevAnimationKeyFrameIndex && !m_activeAnimation.ShouldLoop)
            {
                m_activeAnimation = {};
                return;
            }
            m_prevAnimationKeyFrame = m_activeAnimation.Keys[m_prevAnimationKeyFrameIndex + 0];
            m_nextAnimationKeyFrame = m_activeAnimation.Keys[m_prevAnimationKeyFrameIndex + 1];
            m_currentAnimationState = m_prevAnimationKeyFrame;
            m_timelinePosition = 0;
        }
    }
} // namespace ia::iae