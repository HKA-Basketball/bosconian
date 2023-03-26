#include "../../Resources/fonts.h"
#include "Renderer.h"

namespace Renderer {
    RendererSDL::RendererSDL(Window *window, Uint32 flags) {
        renderer = SDL_CreateRenderer(window->sdl_HWND, -1, flags);

        if (!renderer) {
            LOG(std::string("Error: Could not create Renderer: ") + SDL_GetError());
            return;
        }
        LOG(std::string("Renderer Successfully created"));

        m_fonts.resize(FONT_MAX);

        if (!initSDL_TTF())
            return;

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
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // TODO: add GlobalVars ==> BG color
        SDL_RenderClear(renderer);
        //SDL_DestroyTexture(texture);
    }

    void RendererSDL::endScene() {
        SDL_RenderPresent(renderer);
    }

    void RendererSDL::clearScene() {

    }

    void RendererSDL::clearAll() {
        SDL_DestroyRenderer(renderer);

        //SDL_FreeSurface(surface);
        //SDL_DestroyTexture(texture);

        for (auto font : m_fonts)
        {
            TTF_CloseFont(font);
        }
        TTF_Quit();
        // TODO: add TTF_CloseFont(), TTF_Quit(), SDL_DestroyTexture (for imgs), SDL_FreeSurface
    }

    //--------- Renderer D3D -------------

    /*RendererD3D::RendererD3D(Window *window) {

    }*/


} // Renderer