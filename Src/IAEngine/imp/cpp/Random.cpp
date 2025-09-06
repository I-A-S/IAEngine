#include <IAEngine/Random.hpp>

#include <IAEngine/Time.hpp>

namespace ia::iae
{
    VOID Random::Initialize()
    {
        srand((INT32)Time::GetCurrentTick());
    }

    FLOAT32 Random::Get()
    {
        return (FLOAT32)rand()/(FLOAT32)(RAND_MAX);
    }

    INT32 Random::GetInRange(IN INT32 min, IN INT32 max)
    {
        return min + (INT32)((max - min) * Get());
    }
} // namespace ia::iae