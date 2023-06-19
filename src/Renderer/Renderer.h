#ifndef BOSCONIAN_RENDERER_H
#define BOSCONIAN_RENDERER_H

#include "../../includes.h"
#include "Window.h"
//#include <d3d9.h>
//#include <d3dx9.h>

namespace Renderer {

    enum : uint32_t
    {
        FONT_JOYSTIX_38PX = 0,
        FONT_JOYSTIX_16PX,
        //Space for more
        FONT_MAX
    };

    class RendererSDL {
    private:
        bool initSDL_TTF();
        bool addFont(const void* mem, int size, int fontIndex, int fontPT);

    public:
        std::vector<TTF_Font*> m_fonts;
        SDL_Renderer* renderer;

        RendererSDL(Window* window, Uint32 flags);

        ~RendererSDL() {
            // Clean up the fonts in the m_fonts vector
            for (TTF_Font* font : m_fonts) {
                TTF_CloseFont(font);
            }
            m_fonts.clear();
            TTF_Quit();

            // Clean up the renderer
            if (renderer != nullptr) {
                SDL_DestroyRenderer(renderer);
                renderer = nullptr;
            }
        }

        void beginScene();
        void endScene();
    }; extern RendererSDL* g_renderer;

    /*class RendererD3D {
    private:
        LPDIRECT3D9 d3;
        LPDIRECT3DDEVICE9 d3dev;

    public:
        std::vector<LPD3DXFONT> m_fonts;
        ID3DXLine* d3Line;

        RendererD3D(Window* window);

        void beginScene();
        void endScene();
        void clearScene();

        void clearAll();
    };*/

} // Renderer

#endif //BOSCONIAN_RENDERER_H
