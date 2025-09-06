#include <IAEngine/Random.hpp>
#include <IAEngine/Time.hpp>

#include <chrono>

namespace ia::iae
{
    STATIC CONSTEXPR FLOAT32 TIME_SCALE = 1.0f;

    FLOAT32 g_deltaTime{1 / 60.0f};
    INT64 g_lastFrameTick{0};

    std::chrono::time_point<std::chrono::high_resolution_clock> g_startMS;

    FLOAT32 TimePeriod::GetValue() CONST
    {
        return (FLOAT32) m_value + ((FLOAT32) m_value * (Random::Get() * m_randomAdjustment) / 100.0f);
    }

    VOID Time::Initialize()
    {
        g_startMS = std::chrono::high_resolution_clock::now();
    }

    VOID Time::NextFrame()
    {
        const auto t = GetCurrentTick();
        g_deltaTime = t - g_lastFrameTick;
        g_lastFrameTick = t;
    }

    FLOAT32 Time::GetFrameDeltaTime()
    {
        return g_deltaTime * TIME_SCALE;
    }

    INT64 Time::GetCurrentSecond()
    {
        return std::chrono::duration_cast<std::chrono::seconds>(std::chrono::high_resolution_clock::now() - g_startMS)
            .count();
    }

    INT64 Time::GetCurrentTick()
    {
        return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() -
                                                                     g_startMS)
            .count();
    }
} // namespace ia::iae