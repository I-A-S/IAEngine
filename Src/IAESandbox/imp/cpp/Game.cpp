#include <Game.hpp>
#include <Player.hpp>
#include <Ground.hpp>

#include <IAEngine/ResourceManager.hpp>

namespace ia::iae::game
{
    RefPtr<iae::Scene> scene;

    ResourceManager* g_resourceManager{};

    VOID Game::Initialize()
    {
        g_resourceManager = m_engine->RegisterResourceManager<ResourceManager>();

        scene = m_engine->CreateScene();
        m_engine->ChangeScene(scene);

        const auto player = MakeRefPtr<Player>(m_engine);
        player->SetLocalPosition({100.0f, 200.0f, 0.0f});
        scene->AddNode(player);

        const auto ground = MakeRefPtr<Ground>(m_engine);
        ground->SetLocalPosition({50.0f, 500.0f, 0.0f});
        scene->AddNode(ground);
    }

    VOID Game::Terminate()
    {

    }

    VOID Game::Update()
    {

    }
}