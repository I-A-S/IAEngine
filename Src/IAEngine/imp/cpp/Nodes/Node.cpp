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
        BOOL drew = false;
        for (auto &n : m_children)
        {
            if (((INT32) n->GetPosition().Z) >= 0)
                continue;
            n->Draw();
        }

        if(((INT32) GetPosition().Z) < 0)
        {
            for (auto &c : m_components)
                c->Draw();
        }

        for (INT32 i = 0; i < 8; i++) // [IATODO]
        {
            for (auto &n : m_children)
            {
                if (((INT32) n->GetPosition().Z) != i)
                    continue;
                n->Draw();
            }
            if (((INT32) GetPosition().Z) == i)
            {
                for (auto &c : m_components)
                    c->Draw();
            }
        }

        for (auto &n : m_children)
        {
            if (((INT32) n->GetPosition().Z) < 8)
                continue;
            n->Draw();
        }

        if(((INT32) GetPosition().Z) > 8)
        {
            for (auto &c : m_components)
                c->Draw();
        }
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

    VOID Node::AddChild(IN RefPtr<Node> node)
    {
        m_children.pushBack(node);
    }

    VOID Node::AddComponent(IN RefPtr<IComponent> component)
    {
        m_components.pushBack(IA_MOVE(component));
    }
} // namespace ia::iae