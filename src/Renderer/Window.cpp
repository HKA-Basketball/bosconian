#include "Window.h"

namespace Renderer {

    Window::Window(const char *title, int width, int height, Uint32 flags)
    {
        if (!initSDL())
            throw std::runtime_error("Failed to init SDL");

        windowW = width;
        windowH = height;

        sdl_HWND = SDL_CreateWindow(title,
                                    SDL_WINDOWPOS_CENTERED,
                                    SDL_WINDOWPOS_CENTERED,
                                    width, height,
                                    flags);

        if (!sdl_HWND) {
            LOG(std::string("Error: Could not create Window: ") + SDL_GetError());
            throw std::runtime_error("Failed to create Window");
        }
        LOG(std::string("Window Successfully created"));
    }

    bool Window::initSDL()
    {
        SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "2"); // needed?

        if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
        {
            LOG(std::string("Error initializing SDL: ") + SDL_GetError());
            return 0;
        }
        LOG(std::string("SDL Successfully loaded"));

        return 1;
    }
} // Renderer