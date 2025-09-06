#include <IAEngine/Scene.hpp>

namespace ia::iae
{
    Scene::Scene(IN Engine *engine) : m_engine(engine)
    {
    }

    Scene::~Scene()
    {
    }

    VOID Scene::Draw()
    {
        for (auto &n : m_nodes)
            n->Draw();
    }

    VOID Scene::Update()
    {
        for (auto &n : m_nodes)
            n->Update();
    }

    VOID Scene::AddNode(IN RefPtr<Node> node)
    {
        m_nodes.pushBack(node);
        node->OnAdded(this);
    }

    VOID Scene::RemoveNode(IN RefPtr<Node> node)
    {
        const auto it = m_nodes.find(node);
        if(it != m_nodes.end())
        {
            m_nodes.erase(it);
            node->OnRemoved();
        }        
    }
} // namespace ia::iae