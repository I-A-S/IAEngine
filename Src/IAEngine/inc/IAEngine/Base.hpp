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

#include <IACore/Vector.hpp>
#include <IACore/Memory.hpp>
#include <IACore/String.hpp>
#include <IACore/Exception.hpp>

#include <IAMath/Vec.hpp>

#define IAE_LOG_INFO  ia::iae::LogInfo
#define IAE_LOG_WARN  ia::iae::LogWarn
#define IAE_LOG_ERROR ia::iae::LogError

namespace ia::iae
{
    using Handle = INT64;
    STATIC CONSTEXPR Handle INVALID_HANDLE = -1;

    template<typename... Args> VOID LogInfo(Args... args)
    {
        StringStream ss;
        UNUSED((ss << ... << args));
        printf(__CC_GREEN "[INFO]: %s\n" __CC_DEFAULT, ss.str().c_str());
    }

    template<typename... Args> VOID LogWarn(Args... args)
    {
        StringStream ss;
        UNUSED((ss << ... << args));
        printf(__CC_YELLOW "[WARN]: %s\n" __CC_DEFAULT, ss.str().c_str());
    }

    template<typename... Args> VOID LogError(Args... args)
    {
        StringStream ss;
        UNUSED((ss << ... << args));
        printf(__CC_RED "[ERROR]: %s\n" __CC_DEFAULT, ss.str().c_str());
    }
} // namespace ia::iae