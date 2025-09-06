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

#include <IAEngine/Nodes/Node.hpp>

namespace ia::iae
{
    class Engine;

    class Scene
    {
      public:
        Scene(IN Engine* engine);
        ~Scene();

        VOID Draw();
        VOID Update();

      public:
        VOID AddNode(IN RefPtr<Node> node);
        VOID RemoveNode(IN RefPtr<Node> node);

      public:
        CONST Vector<RefPtr<Node>> &GetNodes() CONST
        {
            return m_nodes;
        }

      private:
        Engine* CONST m_engine;
        Vector<RefPtr<Node>> m_nodes;
    };
} // namespace ia::iae