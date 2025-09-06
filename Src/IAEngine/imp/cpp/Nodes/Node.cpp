#include <IAEngine/Nodes/Node.hpp>

#include <IAEngine/IAEngine.hpp>

namespace ia::iae
{
    VOID Node::OnAdded(IN Scene *scene)
    {
        m_scene = scene;
        for (auto &c : m_children)
            c->OnAdded(scene);
    }

    VOID Node::OnRemoved()
    {
        for (auto &c : m_children)
            c->OnRemoved();
        m_scene = nullptr;
    }

    VOID Node::Draw()
    {
        for (auto &c : m_components)
            c->Draw();

        for (auto &c : m_children)
            c->Draw();
    }

    VOID Node::Update()
    {
        for (auto &c : m_components)
            c->Update();

        for (auto &c : m_children)
            c->Update();
    }

    VOID Node::Enable()
    {
        for (auto &c : m_children)
            c->Enable();
        m_isEnabled = true;
    }

    VOID Node::Disable()
    {
        m_isEnabled = false;
        for (auto &c : m_children)
            c->Disable();
    }

    VOID Node::AddComponent(IN RefPtr<IComponent> component)
    {
        m_components.pushBack(IA_MOVE(component));
    }
} // namespace ia::iae