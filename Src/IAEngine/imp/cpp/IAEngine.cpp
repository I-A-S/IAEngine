#include <IAEngine/Audio.hpp>
#include <IAEngine/IAEngine.hpp>
#include <IAEngine/Input.hpp>
#include <IAEngine/Random.hpp>
#include <IAEngine/Time.hpp>

#include <SDL3/SDL.h>

#include <backends/imgui_impl_sdl3.h>
#include <backends/imgui_impl_sdlrenderer3.h>
#include <imgui.h>

namespace ia::iae
{
    struct EngineContext
    {
        SDL_Renderer *Renderer{};
        SDL_Window *Window{};
        SDL_Event Event{};
        ImGuiIO ImGUIIO{};

        BOOL ShouldClose{false};
    };
} // namespace ia::iae

namespace ia::iae
{
    CONSTEXPR FLOAT32 GAME_UPDATE_INTERVAL = 1000.0f / 60.0f;

    Engine::Engine() : m_context(MakeRefPtr<EngineContext>())
    {
    }

    Engine::~Engine()
    {
    }

    BOOL Engine::Initialize(IN CONST InitConfig &config)
    {
        IAE_LOG_INFO("Booting IAEngine for \"", config.GameName, "\"");

        if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_GAMEPAD))
        {
            IAE_LOG_ERROR("Couldn't intialize SDL3: ", SDL_GetError());
            return false;
        }

        if (!SDL_CreateWindowAndRenderer(config.GameName.c_str(), config.WindowWidth, config.WindowHeight,
                                         SDL_WINDOW_RESIZABLE, &m_context->Window, &m_context->Renderer))
        {
            IAE_LOG_ERROR("Couldn't create SDL3 window and renderer: ", SDL_GetError());
            return false;
        }

        SDL_SetWindowResizable(m_context->Window, false);
        SDL_SetRenderVSync(m_context->Renderer, 1);

        const auto mainScale = SDL_GetDisplayContentScale(SDL_GetPrimaryDisplay());

        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        m_context->ImGUIIO = ImGui::GetIO();
        (void) m_context->ImGUIIO;
        m_context->ImGUIIO.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        m_context->ImGUIIO.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

        ImGui::StyleColorsClassic();

        ImGuiStyle &style = ImGui::GetStyle();
        style.ScaleAllSizes(mainScale);
        style.FontScaleDpi = mainScale;

        ImGui_ImplSDL3_InitForSDLRenderer(m_context->Window, m_context->Renderer);
        ImGui_ImplSDLRenderer3_Init(m_context->Renderer);

        Time::Initialize();
        Random::Initialize();
        Input::Initialize();
        Audio::Initialize();

        return true;
    }

    VOID Engine::Terminate()
    {
        IAE_LOG_INFO("Shutting down IAEngine");

        Audio::Terminate();

        ImGui_ImplSDLRenderer3_Shutdown();
        ImGui_ImplSDL3_Shutdown();
        ImGui::DestroyContext();

        SDL_DestroyRenderer(m_context->Renderer);
        SDL_DestroyWindow(m_context->Window);

        SDL_Quit();
    }

    VOID Engine::BeginFrame()
    {
        SDL_PollEvent(&m_context->Event);
        if (m_context->Event.type == SDL_EVENT_QUIT)
            m_context->ShouldClose = true;
        ProcessEvents();
        m_updateTimer += Time::GetFrameDeltaTime();
        if (m_updateTimer >= GAME_UPDATE_INTERVAL)
        {
            UpdateGame();
            while (m_updateTimer >= GAME_UPDATE_INTERVAL)
                m_updateTimer -= GAME_UPDATE_INTERVAL;
        }
        ImGui_ImplSDLRenderer3_NewFrame();
        ImGui_ImplSDL3_NewFrame();
        ImGui::NewFrame();
        RenderDebugUI();
        ImGui::Render();
        SDL_SetRenderScale(m_context->Renderer, m_context->ImGUIIO.DisplayFramebufferScale.x,
                           m_context->ImGUIIO.DisplayFramebufferScale.y);
        SDL_SetRenderDrawColorFloat(m_context->Renderer, 0.33f, 0.33f, 0.33f, 1.0f);
        SDL_RenderClear(m_context->Renderer);
        RenderGame();
    }

    VOID Engine::EndFrame()
    {
        ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), m_context->Renderer);
        SDL_RenderPresent(m_context->Renderer);
        Time::NextFrame();
    }

    BOOL Engine::ShouldClose()
    {
        return m_context->ShouldClose;
    }

    VOID Engine::RenderDebugUI()
    {
    }

    VOID Engine::ProcessEvents()
    {
        Input::OnEvent(&m_context->Event);
    }

    VOID Engine::UpdateGame()
    {
        if B_LIKELY (m_activeScene)
            m_activeScene->Update();
    }

    VOID Engine::RenderGame()
    {
        if B_LIKELY (m_activeScene)
            m_activeScene->Draw();
    }

    VOID Engine::ChangeScene(IN RefPtr<Scene> scene)
    {
        m_activeScene = scene;
    }

    RefPtr<Scene> Engine::CreateScene()
    {
        return MakeRefPtr<Scene>(this);
    }

    PVOID Engine::GetRendererHandle() CONST
    {
        return m_context->Renderer;
    }
} // namespace ia::iae
