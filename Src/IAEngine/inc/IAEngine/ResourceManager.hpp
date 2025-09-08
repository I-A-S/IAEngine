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

#include <IAEngine/Audio.hpp>
#include <IAEngine/Texture.hpp>

namespace ia::iae
{
    class Engine;

    class ResourceManager
    {
      public:
        RefPtr<Texture> CreateTexture(IN CONST Span<CONST UINT8> &encodedData);
        RefPtr<Texture> CreateTexture(IN PCUINT8 encodedData, IN SIZE_T encodedDataSize);
        RefPtr<Texture> CreateTexture(IN PCUINT8 rgbaData, IN INT32 width, IN INT32 height);

      public:
        Sound CreateSound(IN PCUINT8 audioData, IN SIZE_T audioDataSize)
        {
            return Audio::CreateSound(audioData, audioDataSize);
        }

        Sound CreateSound(IN CONST Vector<UINT8> &audioData)
        {
            return CreateSound(audioData.data(), audioData.size());
        }

      protected:
        Engine *CONST m_engine;

        ResourceManager(IN Engine *engine);
        friend class Engine;
    };
} // namespace ia::iae