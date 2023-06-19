#ifndef BOSCONIAN_WINDOW_H
#define BOSCONIAN_WINDOW_H

#include "../../includes.h"

namespace Renderer {

    class Window {
    private:
        bool initSDL();

    public:
        SDL_Window* sdl_HWND;
        int windowW, windowH;

        Window(const char* title, int width, int height, Uint32 flags);

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
