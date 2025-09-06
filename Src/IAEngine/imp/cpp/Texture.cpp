#include <IAEngine/IAEngine.hpp>
#include <IAEngine/Texture.hpp>

#include <SDL3/SDL.h>

#define TEXTURE_HANDLE (SDL_Texture *) m_handle

namespace ia::iae
{
    Texture::Texture(IN Engine *engine) : m_engine(engine)
    {
    }

    Texture::~Texture()
    {
        SDL_DestroyTexture(TEXTURE_HANDLE);
    }

    VOID Texture::Draw(IN CONST iam::Vec3f &position, IN CONST iam::Vec3f &scale, IN FLOAT32 rotation, IN BOOL flipH,
                       IN BOOL flipV, IN CONST iam::Vec4f &colorOverlay) CONST
    {
        SDL_FRect rect{.x = position.X, .y = position.Y, .w = m_width * scale.X, .h = m_height * scale.Y};

        SDL_SetTextureColorModFloat(TEXTURE_HANDLE, colorOverlay.X, colorOverlay.Y, colorOverlay.Z);
        SDL_SetTextureAlphaModFloat(TEXTURE_HANDLE, colorOverlay.W);
        SDL_RenderTextureRotated((SDL_Renderer *) m_engine->GetRendererHandle(), TEXTURE_HANDLE, nullptr, &rect,
                                 rotation, nullptr,
                                 (SDL_FlipMode) (SDL_FLIP_NONE | (flipV ? SDL_FLIP_VERTICAL : SDL_FLIP_NONE) |
                                                 (flipH ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE)));
    }
} // namespace ia::iae