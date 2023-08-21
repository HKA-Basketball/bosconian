#ifndef BOSCONIAN_RENDERER_H
#define BOSCONIAN_RENDERER_H

#include "../../includes.h"
#include "Window.h"
//#include <d3d9.h>
//#include <d3dx9.h>

namespace Renderer {

    /**
     * Enum to represent different fonts.
     */
    enum : uint32_t
    {
        FONT_JOYSTIX_38PX = 0,  // Larger Joystix font
        FONT_JOYSTIX_16PX,      // Smaller Joystix font
        // Space for more font options
        FONT_MAX                // Maximum number of font options
    };

    /**
     * \class RendererSDL
     * \brief A class for managing SDL rendering and fonts.
     */
    class RendererSDL {
    private:
        /**
         * Initialize the SDL TTF library for font rendering.
         * \return True if initialization was successful, false otherwise.
         */
        bool initSDL_TTF();

        /**
         * Add a font from memory to the renderer.
         * \param mem Pointer to the memory containing the font data.
         * \param size Size of the font data in bytes.
         * \param fontIndex Index of the font to add.
         * \param fontPT Point size of the font.
         * \return True if adding the font was successful, false otherwise.
         */
        bool addFont(const void* mem, int size, int fontIndex, int fontPT);

    public:
        std::vector<TTF_Font*> m_fonts; // Vector to store TTF_Font pointers
        SDL_Renderer* renderer;         // Pointer to the SDL renderer

        /**
         * Constructor for the RendererSDL class.
         * \param window Pointer to the SDL Window.
         * \param flags Flags to control the renderer behavior (e.g., SDL_RENDERER_ACCELERATED).
         */
        RendererSDL(Window* window, Uint32 flags);

        /**
         * Destructor for the RendererSDL class.
         * Cleans up allocated TTF_Font objects and the SDL renderer.
         */
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

        /**
         * Begin rendering a scene.
         */
        void beginScene();

        /**
         * End rendering a scene.
         */
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
