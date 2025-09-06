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
#include <IAEngine/Components/Component.hpp>

namespace ia::iae
{
    class SoundEmitterComponent : public IComponent
    {
      public:
        SoundEmitterComponent(IN Node *node);
        ~SoundEmitterComponent();

        VOID Pause();
        VOID Resume();

        VOID SetSound(IN CONST Sound &sound);

      public:
        VOID Draw();
        VOID Update();

      private:
        INT64 m_trackHandle{INVALID_HANDLE};
        Sound m_activeSound{INVALID_HANDLE};
    };
} // namespace ia::iae