#include <IAEngine/Audio.hpp>

#include <SDL3/SDL_iostream.h>
#include <SDL3_mixer/SDL_mixer.h>

#include <thread>

namespace ia::iae
{
    MIX_Mixer *g_mixer{};
    Vector<MIX_Track *> g_tracks;
    Vector<MIX_Audio *> g_audioData;

    VOID Audio::Initialize()
    {
        if (!MIX_Init())
            THROW_UNKNOWN("Couldn't initialize SDL3 Mixer");

        if (!(g_mixer = MIX_CreateMixerDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, NULL)))
            THROW_UNKNOWN(BuildString("Creating a SDL3 mixer failed with code ", SDL_GetError()));
    }

    VOID Audio::Terminate()
    {
        g_audioData.clear();
    }

    Sound Audio::CreateSound(IN PCUINT8 audioData, IN SIZE_T audioDataSize)
    {
        g_audioData.pushBack(MIX_LoadAudio_IO(g_mixer, SDL_IOFromConstMem(audioData, audioDataSize), false, true));
        return Sound(g_audioData.size() - 1);
    }

    INT64 Audio::CreateTrack()
    {
        g_tracks.pushBack(MIX_CreateTrack(g_mixer));
        return g_tracks.size() - 1;
    }

    VOID Audio::DestroyTrack(IN INT64 trackHandle)
    {
        ClearTrack(trackHandle);
    }

    VOID Audio::QueueTrackData(IN INT64 trackHandle, IN INT64 dataHandle)
    {
        MIX_SetTrackAudio(g_tracks[trackHandle], g_audioData[dataHandle]);
    }

    VOID Audio::PlayTrack(IN INT64 trackHandle, IN INT32 loopTimes, IN TimePeriod loopDelay)
    {
        struct __callback_data
        {
            INT32 loopTimes;
            TimePeriod loopDelay;
        };

        const auto callbackData = new __callback_data{.loopTimes = loopTimes, .loopDelay = loopDelay};

        MIX_PlayTrack(g_tracks[trackHandle], 0);
        MIX_SetTrackStoppedCallback(
            g_tracks[trackHandle],
            [](PVOID _callbackData, MIX_Track *track) {
                const auto callbackData = (__callback_data *) _callbackData;
                if (callbackData->loopTimes < 0)
                    goto loop_next_iteration;
                else if (callbackData->loopTimes == 0)
                    return;
                else
                    callbackData->loopTimes -= 1;
            loop_next_iteration:
                std::this_thread::sleep_for(std::chrono::milliseconds((INT32) (callbackData->loopDelay.GetValue() * 1000)));
                MIX_PlayTrack(track, 0);
            },
            callbackData);
    }

    VOID Audio::ClearTrack(IN INT64 trackHandle)
    {
        //MIX_StopTrack(g_tracks[trackHandle], 0);
    }

    VOID Audio::PauseTrack(IN INT64 trackHandle)
    {
        MIX_PauseTrack(g_tracks[trackHandle]);
    }

    VOID Audio::ResumeTrack(IN INT64 trackHandle)
    {
        MIX_ResumeTrack(g_tracks[trackHandle]);
    }
} // namespace ia::iae