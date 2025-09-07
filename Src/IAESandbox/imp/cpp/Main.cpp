#include <Game.hpp>

ia::iae::Engine g_engine;

int main(int argc, char *argv[])
{
    g_engine.Initialize({.GameName = "IAE Sandbox", .WindowWidth = 800, .WindowHeight = 600});
    const auto game = new ia::iae::game::Game(&g_engine);
    game->Initialize();
    while (!g_engine.ShouldClose())
    {
        g_engine.BeginFrame();
        game->Update();
        g_engine.EndFrame();
    }
    game->Terminate();
    delete game;
    g_engine.Terminate();
    return 0;
}