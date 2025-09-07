#pragma once

#include <IAEngine/IAEngine.hpp>

namespace ia::iae::game
{
    class Game
    {
    public:
        Game(IN Engine* engine): m_engine(engine) {}
    
        VOID Initialize();
        VOID Terminate();
        VOID Update();

    private:
        Engine* CONST m_engine;
    };
}