// IAEngine: 2D ECS Game Engine.
// Copyright (C) 2026 IAS (ias@iasoft.dev)
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <iaengine/engine.hpp>
#include <iaengine/providers/render.hpp>

#include <SDL3/SDL.h>

#include <backends/imgui_impl_sdl3.h>
#include <backends/imgui_impl_sdlgpu3.h>

namespace iae
{
  ImGuiIO g_imgui_io{};

  auto RenderProvider::initialize() -> Result<void>
  {
    SDL_GPUDevice *device{};

    const auto device_create_props = SDL_CreateProperties();
    SDL_SetStringProperty(device_create_props, SDL_PROP_GPU_DEVICE_CREATE_NAME_STRING, nullptr);
    SDL_SetBooleanProperty(device_create_props, SDL_PROP_GPU_DEVICE_CREATE_SHADERS_SPIRV_BOOLEAN, true);
    SDL_SetBooleanProperty(device_create_props, SDL_PROP_GPU_DEVICE_CREATE_DEBUGMODE_BOOLEAN,
#if defined(NDEBUG)
                           false
#else
                           true
#endif
    );
    SDL_SetBooleanProperty(device_create_props, SDL_PROP_GPU_DEVICE_CREATE_FEATURE_DEPTH_CLAMPING_BOOLEAN, true);
    if (!(device = SDL_CreateGPUDeviceWithProperties(device_create_props)))
      return fail("Failed to create the SDL GPU Device: '%s'", SDL_GetError());
    SDL_DestroyProperties(device_create_props);

    const auto window_handle = (SDL_Window *) Engine::instance().get_display_provider().get_window_handle();

    if (!SDL_ClaimWindowForGPUDevice(device, window_handle))
      return fail("Failed to initialize SDL GPU for the window: '%s'", SDL_GetError());

    SDL_SetGPUSwapchainParameters(device, window_handle, SDL_GPU_SWAPCHAINCOMPOSITION_SDR, SDL_GPU_PRESENTMODE_VSYNC);

    SDL_GetWindowSizeInPixels(window_handle, &m_width, &m_height);
    resize(m_width, m_height, true);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    g_imgui_io = ImGui::GetIO();
    g_imgui_io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    g_imgui_io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

    ImGui::StyleColorsClassic();

    const auto main_scale = SDL_GetDisplayContentScale(SDL_GetPrimaryDisplay());
    ImGuiStyle &style = ImGui::GetStyle();
    style.ScaleAllSizes(main_scale);
    style.FontScaleDpi = main_scale;

    ImGui_ImplSDLGPU3_InitInfo init_info{.Device = device,
                                         .ColorTargetFormat = SDL_GetGPUSwapchainTextureFormat(device, window_handle),
                                         .PresentMode = SDL_GPU_PRESENTMODE_VSYNC};
    ImGui_ImplSDL3_InitForSDLGPU(window_handle);
    ImGui_ImplSDLGPU3_Init(&init_info);

    m_device_handle = device;

    return {};
  }

  auto RenderProvider::terminate() -> void
  {
    const auto device = (SDL_GPUDevice *) m_device_handle;

    SDL_WaitForGPUIdle(device);

    ImGui_ImplSDL3_Shutdown();
    ImGui_ImplSDLGPU3_Shutdown();
    ImGui::DestroyContext();

    SDL_ReleaseWindowFromGPUDevice(device,
                                   (SDL_Window *) Engine::instance().get_display_provider().get_window_handle());
    SDL_DestroyGPUDevice(device);
  }

  auto RenderProvider::begin_frame() -> void
  {
    const auto device = (SDL_GPUDevice *) m_device_handle;

    SDL_GPUCommandBuffer *cmdbuffer;
    if (!(cmdbuffer = SDL_AcquireGPUCommandBuffer(device)))
      return;

    SDL_GPUTexture *swap_chain_texture{};
    if (!SDL_WaitAndAcquireGPUSwapchainTexture(
            cmdbuffer, (SDL_Window *) Engine::instance().get_display_provider().get_window_handle(),
            &swap_chain_texture, (u32 *) &m_width, (u32 *) &m_height) ||
        !swap_chain_texture)
      return;

    ImGui_ImplSDLGPU3_NewFrame();
    ImGui_ImplSDL3_NewFrame();
    ImGui::NewFrame();
    // [IATODO]: DebugDraw handler
    ImGui::Render();
    const auto imdraw_data = ImGui::GetDrawData();
    ImGui_ImplSDLGPU3_PrepareDrawData(imdraw_data, cmdbuffer);
    m_imdraw_data = imdraw_data;

    SDL_GPUColorTargetInfo color_target{
        .texture = swap_chain_texture,
        .clear_color = SDL_FColor(100.0f / 255.0f, 149.0f / 255.0f, 237.0f / 255.0f, 1),
        .load_op = SDL_GPU_LOADOP_CLEAR,
        .store_op = SDL_GPU_STOREOP_STORE,
    };
    SDL_GPURenderPass *renderpass = SDL_BeginGPURenderPass(cmdbuffer, &color_target, 1, nullptr);

    m_cmdbuffer_handle = cmdbuffer;
    m_renderpass_handle = renderpass;
  }

  auto RenderProvider::end_frame() -> void
  {
    const auto cmdbuffer = (SDL_GPUCommandBuffer *) m_cmdbuffer_handle;
    const auto renderpass = (SDL_GPURenderPass *) m_renderpass_handle;

    ImGui_ImplSDLGPU3_RenderDrawData((ImDrawData *) m_imdraw_data, cmdbuffer, renderpass);

    SDL_EndGPURenderPass(renderpass);

    SDL_SubmitGPUCommandBuffer(cmdbuffer);
  }

  auto RenderProvider::resize(i32 width, i32 height, bool force_resize) -> void
  {
    if (!force_resize && (width == m_width) && (height == m_height))
      return;
  }

  auto RenderProvider::process_event(const SDL_Event &event) -> void
  {
    switch (event.type)
    {
    case SDL_EVENT_WINDOW_RESIZED:
      resize(event.window.data1, event.window.data2);
      break;
    }
    ImGui_ImplSDL3_ProcessEvent(&event);
  }

  auto RenderProvider::create_texture(const u8 *rgba, i32 width, i32 height) -> Result<ResourceHandle>
  {
    return NULL_RESOURCE;
  }
} // namespace iae