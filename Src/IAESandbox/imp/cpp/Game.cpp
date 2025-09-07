#include <Game.hpp>
#include <Player.hpp>
#include <Map.hpp>

namespace ia::iae::game
{
    RefPtr<iae::Scene> scene;

    VOID Game::Initialize()
    {
        const auto player = MakeRefPtr<Player>(m_engine);
        player->SetLocalPosition({200, 150, 0});

        const auto map = MakeRefPtr<TiledMap>(m_engine);

        scene = m_engine->CreateScene();
        scene->AddNode(map);
        scene->AddNode(player);

        m_engine->ChangeScene(scene);

        
    }

    VOID Game::Terminate()
    {

    }

    VOID Game::Update()
    {

    }
}