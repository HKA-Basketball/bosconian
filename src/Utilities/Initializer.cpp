#include "Initializer.h"

namespace Initialization {
    Initializer* Initializer::instance = nullptr;

    bool Initializer::initGameObjs() {

        if (isInit) {
            LOG(std::string("Already Initialized!"));
            return 1;
        }

        g_window = new Renderer::Window("Bosconian - Playing", Utils::GlobalVars::windowWidth + Utils::GlobalVars::infoWidth, Utils::GlobalVars::windowHeight, SDL_WINDOW_ALLOW_HIGHDPI);

        if (!g_window) {
            LOG(std::string("Could not create window: ") + SDL_GetError());
            return 0;
        }

        g_renderer = new Renderer::RendererSDL(g_window, SDL_RENDERER_ACCELERATED /*| SDL_RENDERER_PRESENTVSYNC*/);

        if (!g_renderer) {
            g_renderer->clearAll();
            SDL_DestroyWindow(g_window->sdl_HWND);
            SDL_Quit();
            return 0;
        }

        g_drawing = new Drawing::Graphics(g_renderer);
        if (!g_drawing) {
            g_renderer->clearAll();
            SDL_DestroyWindow(g_window->sdl_HWND);
            SDL_Quit();
            return 0;
        }

        g_world = new Game::World(g_drawing);
        if (!g_world) {
            g_renderer->clearAll();
            SDL_DestroyWindow(g_window->sdl_HWND);
            SDL_Quit();
            return 0;
        }

        g_event = new Event::EventManager();
        if (!g_event)
        {
            LOG(std::string("Error: EventManager"));
            g_renderer->clearAll();
            SDL_DestroyWindow(g_window->sdl_HWND);
            SDL_Quit();
            return 0;
        }

        g_sound = new Sound::SoundManager();
        if (!g_sound)
        {
            LOG(std::string("Error: EventManager"));
            g_renderer->clearAll();
            SDL_DestroyWindow(g_window->sdl_HWND);
            SDL_Quit();
            return 0;
        }

        isInit = true;

        return 1;
    }

    Renderer::Window *Initializer::window() const {
        return g_window;
    }

    Renderer::RendererSDL *Initializer::renderer() const {
        return g_renderer;
    }

    Drawing::Graphics *Initializer::drawing() const {
        return g_drawing;
    }

    Game::World *Initializer::world() const {
        return g_world;
    }

    Event::EventManager *Initializer::event() const {
        return g_event;
    }

    Sound::SoundManager *Initializer::sound() const {
        return g_sound;
    }
} // Initialization