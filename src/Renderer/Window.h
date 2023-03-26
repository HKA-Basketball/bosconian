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


    };

} // Renderer

#endif //BOSCONIAN_WINDOW_H
