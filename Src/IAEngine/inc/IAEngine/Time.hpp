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

#include <IAEngine/Base.hpp>

namespace ia::iae
{
    class TimePeriod
    {
      public:
        TimePeriod()
        {
        }

        TimePeriod(IN INT32 value, IN INT32 randomAdjustment)
        {
            SetValue(value);
            SetRandomAdjustment(randomAdjustment);
        }

        VOID SetValue(IN INT32 value)
        {
            m_value = value;
        }

        VOID SetRandomAdjustment(IN INT32 adjustment)
        {
            m_randomAdjustment = adjustment;
        }

        FLOAT32 GetValue() CONST;

      private:
        INT32 m_value{};
        INT32 m_randomAdjustment{};
    };

    class Time
    {
      public:
        STATIC VOID Initialize();

        STATIC VOID NextFrame();

        STATIC INT64 GetCurrentTick();
        STATIC INT64 GetCurrentSecond();
        STATIC FLOAT32 GetFrameDeltaTime();
    };
} // namespace ia::iae