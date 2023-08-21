#ifndef BOSCONIAN_WINDOW_H
#define BOSCONIAN_WINDOW_H

#include "../../includes.h"

namespace Renderer {

    /**
     * \class Window
     * \brief A class representing an SDL window.
     */
    class Window {
    private:
        /**
         * Initialize the SDL library.
         * \return True if initialization was successful, false otherwise.
         */
        bool initSDL();

    public:
        SDL_Window* sdl_HWND; // Pointer to the SDL window
        int windowW, windowH; // Width and height of the window

        /**
        * Constructor for the Window class.
        * \param title The title of the window.
        * \param width The width of the window.
        * \param height The height of the window.
        * \param flags Flags to control the window behavior (e.g., SDL_WINDOW_SHOWN).
        */
        Window(const char* title, int width, int height, Uint32 flags);

        /**
         * Destructor for the Window class.
         * Cleans up the allocated SDL window.
         */
        ~Window() {
            // Clean up the SDL window
            if (sdl_HWND != nullptr) {
                SDL_DestroyWindow(sdl_HWND);
                sdl_HWND = nullptr;
            }
        }
    };

} // Renderer

#endif //BOSCONIAN_WINDOW_H
