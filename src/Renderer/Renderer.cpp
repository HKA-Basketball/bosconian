#include "../../Resources/fonts.h"
#include "Renderer.h"

namespace Renderer {
    RendererSDL* g_renderer;

    RendererSDL::RendererSDL(Window *window, Uint32 flags) {
        renderer = SDL_CreateRenderer(window->sdl_HWND, -1, flags);

        if (!renderer) {
            LOG(std::string("Error: Could not create Renderer: ") + SDL_GetError());
            throw std::runtime_error("Failed to creat Renderer");
        }
        LOG(std::string("Renderer Successfully created"));

        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

        m_fonts.resize(FONT_MAX);

        if (!initSDL_TTF())
            throw std::runtime_error("Failed to init SDL_TTF");

        addFont(joystix_ttf, sizeof(joystix_ttf), FONT_JOYSTIX_38PX, 38);
        addFont(joystix_ttf, sizeof(joystix_ttf), FONT_JOYSTIX_16PX, 16);
        // More Fonts here

        LOG(std::string("Fonts Successfully loaded"));
    }

    bool RendererSDL::initSDL_TTF() {
        if (TTF_Init() < 0) {
            LOG(std::string("Error: intializing SDL_ttf: ") + TTF_GetError());
            return 0;
        }

        return 1;
    }

    bool RendererSDL::addFont(const void *mem, int size, int fontIndex, int fontPT) {
        SDL_RWops* pFontMem = SDL_RWFromConstMem(mem, size);

        if(!pFontMem)
        {
            LOG(std::string("Error: loading font Data: ") + TTF_GetError());
            return 0;
        }

        m_fonts[fontIndex] = TTF_OpenFontRW(pFontMem, 1, fontPT);

        if (!m_fonts[fontIndex])
        {
            LOG(std::string("Error: loading font index (") + std::to_string(fontIndex) + std::string("): ") + TTF_GetError());
            return 0;
        }

        return 1;
    }

    void RendererSDL::beginScene() {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        //SDL_DestroyTexture(texture);
    }

    void RendererSDL::endScene() {
        SDL_RenderPresent(renderer);
    }

    //--------- Renderer D3D -------------

    /*RendererD3D::RendererD3D(Window *window) {

    }*/


} // Renderer