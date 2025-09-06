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

#include <IAEngine/Time.hpp>

namespace ia::iae
{
    class Sound
    {
      public:
        Sound(IN INT64 dataHandle) : m_dataHandle(dataHandle)
        {
        }

        INT64 DataHandle() CONST
        {
            return m_dataHandle;
        }

        INT32 LoopTimes() CONST
        {
            return m_loopTimes;
        }

        TimePeriod LoopDelay() CONST
        {
            return m_loopDelay;
        }

        INT32 &LoopTimes()
        {
            return m_loopTimes;
        }

        TimePeriod &LoopDelay()
        {
            return m_loopDelay;
        }

      private:
        INT64 m_dataHandle{};
        INT32 m_loopTimes{0};
        TimePeriod m_loopDelay{};
    };

    class Audio
    {
      public:
        STATIC VOID Initialize();
        STATIC VOID Terminate();

        STATIC Sound CreateSound(IN CONST Vector<UINT8> &audioData)
        {
            return CreateSound(audioData.data(), audioData.size());
        }

        STATIC Sound CreateSound(IN PCUINT8 audioData, IN SIZE_T audioDataSize);

        STATIC INT64 CreateTrack();
        STATIC VOID DestroyTrack(IN INT64 trackHandle);

        STATIC VOID QueueTrackData(IN INT64 trackHandle, IN INT64 dataHandle);
        STATIC VOID PlayTrack(IN INT64 trackHandle, IN INT32 loopTimes, IN TimePeriod loopDelay);
        STATIC VOID ClearTrack(IN INT64 trackHandle);
        STATIC VOID PauseTrack(IN INT64 trackHandle);
        STATIC VOID ResumeTrack(IN INT64 trackHandle);
    };
} // namespace ia::iae