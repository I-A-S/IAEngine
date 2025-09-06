#include <IAEngine/Components/SoundEmitter.hpp>

namespace ia::iae
{
    SoundEmitterComponent::SoundEmitterComponent(IN Node *node):
        IComponent(node)
    {
        m_trackHandle = Audio::CreateTrack();
        SetSound(m_activeSound);
    }

    SoundEmitterComponent::~SoundEmitterComponent()
    {
        Audio::DestroyTrack(m_trackHandle);
        m_trackHandle = INVALID_HANDLE;
    }

    VOID SoundEmitterComponent::Pause()
    {
        Audio::PauseTrack(m_trackHandle);
    }

    VOID SoundEmitterComponent::Resume()
    {
        Audio::ResumeTrack(m_trackHandle);
    }

    VOID SoundEmitterComponent::Draw()
    {
    }

    VOID SoundEmitterComponent::Update()
    {
    }

    VOID SoundEmitterComponent::SetSound(IN CONST Sound &sound)
    {
        m_activeSound = sound;
        if(m_trackHandle == INVALID_HANDLE) return;
        Audio::QueueTrackData(m_trackHandle, sound.DataHandle());
        Audio::PlayTrack(m_trackHandle, sound.LoopTimes(), sound.LoopDelay());
    }
} // namespace ia::iae