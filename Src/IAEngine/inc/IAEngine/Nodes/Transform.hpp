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

#include <IAEngine/Base.hpp>

namespace ia::iae
{
    template<typename _node_type>
    class Transform
    {
      public:
        VOID SetLocalPosition(IN CONST iam::Vec3f &v)
        {
            m_local.Position = v;
            RecalculatePosition();
        }

        VOID SetLocalScale(IN CONST iam::Vec3f &v)
        {
            m_local.Scale = v;
            RecalculateScale();
        }

        VOID SetLocalRotation(IN CONST iam::Vec3f &v)
        {
            m_local.Rotation = v;
            RecalculateRotation();
        }

      public:
        CONST iam::Vec3f &GetPosition() CONST
        {
            return m_global.Position;
        }

        CONST iam::Vec3f &GetScale() CONST
        {
            return m_global.Scale;
        }

        CONST iam::Vec3f &GetRotation() CONST
        {
            return m_global.Rotation;
        }

        CONST iam::Vec3f &GetLocalPosition() CONST
        {
            return m_local.Position;
        }

        CONST iam::Vec3f &GetLocalScale() CONST
        {
            return m_local.Scale;
        }

        CONST iam::Vec3f &GetLocalRotation() CONST
        {
            return m_local.Rotation;
        }

      protected:
        RefPtr<_node_type> m_parent{};
        Vector<RefPtr<_node_type>> m_children{};

      protected:
        VOID RecalculatePosition()
        {
            m_global.Position = (m_parent ? m_parent->GetPosition() : iam::Vec3f{}) + m_local.Position;
            for (auto &c : m_children)
                c->RecalculatePosition();
        }

        VOID RecalculateRotation()
        {
            m_global.Rotation = (m_parent ? m_parent->GetRotation() : iam::Vec3f{}) + m_local.Rotation;
            for (auto &c : m_children)
                c->RecalculateRotation();
        }

        VOID RecalculateScale()
        {
            m_global.Scale = (m_parent ? m_parent->GetScale() : iam::Vec3f{}) + m_local.Scale;
            for (auto &c : m_children)
                c->RecalculateScale();
        }

      private:
        struct
        {
            iam::Vec3f Position{0.0f, 0.0f, 0.0f};
            iam::Vec3f Rotation{0.0f, 0.0f, 0.0f};
            iam::Vec3f Scale{1.0f, 1.0f, 1.0f};
        } m_local{}, m_global{};
    };
} // namespace ia::iae