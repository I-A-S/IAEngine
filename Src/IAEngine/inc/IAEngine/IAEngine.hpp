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
#include <IAEngine/Scene.hpp>
#include <IAEngine/Texture.hpp>
#include <IAEngine/ResourceManager.hpp>

namespace ia::iae
{
    struct EngineContext;

    class Engine
    {
      public:
        struct InitConfig
        {
            String GameName{"IAEngine Game"};
            INT32 WindowWidth{800};
            INT32 WindowHeight{600};
        };

      public:
        Engine();
        ~Engine();

        BOOL Initialize(IN CONST InitConfig &config);
        VOID Terminate();

        VOID BeginFrame();
        VOID EndFrame();
        BOOL ShouldClose();

        template<typename _class_type>
        _class_type* RegisterResourceManager();

      public:
        RefPtr<Scene> CreateScene();

        VOID ChangeScene(IN RefPtr<Scene> scene);

      public:
        PVOID GetRendererHandle() CONST;

      private:
        VOID RenderDebugUI();
        VOID ProcessEvents();
        VOID UpdateGame();
        VOID RenderGame();

      private:
        FLOAT32 m_updateTimer{};
        RefPtr<Scene> m_activeScene{};
        CONST RefPtr<EngineContext> m_context;
        RefPtr<ResourceManager> m_resourceManager;
    };

    template<typename _class_type>
    _class_type* Engine::RegisterResourceManager()
    {
        m_resourceManager = MakeRefPtr<_class_type>(this);
        return (_class_type*)m_resourceManager.get();
    }
} // namespace ia::iae