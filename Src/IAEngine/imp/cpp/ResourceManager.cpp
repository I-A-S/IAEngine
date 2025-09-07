#include <IAEngine/IAEngine.hpp>
#include <IAEngine/ResourceManager.hpp>

#include <SDL3/SDL.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

namespace ia::iae
{
    ResourceManager::ResourceManager(IN Engine *engine) : m_engine(engine)
    {
    }

    RefPtr<Texture> ResourceManager::CreateTexture(IN CONST Span<CONST UINT8> &encodedData)
    {
        return CreateTexture(encodedData.data(), encodedData.size());
    }

    RefPtr<Texture> ResourceManager::CreateTexture(IN PCUINT8 encodedData, IN SIZE_T encodedDataSize)
    {
        INT32 w, h, nrChannels;
        const auto pixels = stbi_load_from_memory(encodedData, encodedDataSize, &w, &h, &nrChannels, STBI_rgb_alpha);
        if (!pixels)
            THROW_INVALID_DATA("Failed to decode the provided image data");
        const auto result = CreateTexture((PCUINT8) pixels, w, h);
        STBI_FREE(pixels);
        return result;
    }

    RefPtr<Texture> ResourceManager::CreateTexture(IN PCUINT8 rgbaData, IN INT32 width, IN INT32 height)
    {
        const auto result = MakeRefPtr<Texture>(m_engine);

        result->m_width = width;
        result->m_height = height;

        SDL_Surface *surface =
            SDL_CreateSurfaceFrom(width, height, SDL_PIXELFORMAT_RGBA32, (void *) rgbaData, width << 2);
        if (!surface)
            THROW_UNKNOWN("Failed to create SDL surface: ", SDL_GetError());
        result->m_handle = SDL_CreateTextureFromSurface((SDL_Renderer *) m_engine->GetRendererHandle(), surface);
        if (!result->m_handle)
            THROW_UNKNOWN("Failed to create SDL Texture: ", SDL_GetError());
        SDL_DestroySurface(surface);

        return result;
    }
} // namespace ia::iae