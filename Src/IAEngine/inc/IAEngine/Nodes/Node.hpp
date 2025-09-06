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

#include <IAEngine/Components/Component.hpp>
#include <IAEngine/Nodes/Transform.hpp>
#include <IAEngine/Texture.hpp>

namespace ia::iae
{
    class Scene;

    class Node : public Transform<Node>
    {
      public:
        VIRTUAL VOID OnAdded(IN Scene* scene);
        VIRTUAL VOID OnRemoved();

        VIRTUAL VOID Draw();
        VIRTUAL VOID Update();
        VIRTUAL VOID Enable();
        VIRTUAL VOID Disable();

      public:
        template<typename _component_type>
        RefPtr<_component_type> AddComponent();

        CONST Vector<RefPtr<IComponent>>& GetComponents() CONST
        {
            return m_components;
        }

      protected:
        Scene* m_scene{};
        BOOL m_isEnabled{true};

      protected:
        Vector<RefPtr<IComponent>> m_components;

        friend class IComponent;

    private:
        VOID AddComponent(IN RefPtr<IComponent> component);
    };

    template<typename _component_type>
    RefPtr<_component_type> Node::AddComponent()
    {
        const auto c = MakeRefPtr<_component_type>(this);
        AddComponent(c);
        return c;
    }
} // namespace ia::iae