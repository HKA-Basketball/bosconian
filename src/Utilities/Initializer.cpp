#include "Initializer.h"

namespace Init {
    Initializer* Initializer::instance = nullptr;

    bool Initializer::initGameObjs() {

        if (isInit) {
            LOG(std::string("Already Initialized!"));
            return 1;
        }

        g_window = new Renderer::Window("Bosconian - Playing", Utils::GlobalVars::windowWidth + Utils::GlobalVars::infoWidth, Utils::GlobalVars::windowHeight, SDL_WINDOW_ALLOW_HIGHDPI);

        if (!g_window) {
            delete this;
            LOG(std::string("Could not create window: ") + SDL_GetError());
            return 0;
        }

        Renderer::g_renderer = new Renderer::RendererSDL(g_window, SDL_RENDERER_ACCELERATED /*| SDL_RENDERER_PRESENTVSYNC*/);

        if (!Renderer::g_renderer) {
            LOG(std::string("Error: RendererSDL"));
            delete this;
            return 0;
        }

        Drawing::g_drawing = new Drawing::Graphics();
        if (!Drawing::g_drawing) {
            LOG(std::string("Error: Graphics"));
            delete this;
            return 0;
        }

        Game::g_world = new Game::World();
        if (!Game::g_world) {
            LOG(std::string("Error: World"));
            delete this;
            return 0;
        }

        Event::g_event = new Event::EventManager();
        if (!Event::g_event)
        {
            LOG(std::string("Error: EventManager"));
            delete this;
            return 0;
        }

        Sound::g_sound = new Sound::SoundManager();
        if (!Sound::g_sound)
        {
            LOG(std::string("Error: SoundManager"));
            delete this;
            return 0;
        }

        isInit = true;

        return 1;
    }

    Renderer::Window *Initializer::window() const {
        return g_window;
    }

    Renderer::RendererSDL *Initializer::renderer() const {
        return Renderer::g_renderer;
    }

    Drawing::Graphics *Initializer::drawing() const {
        return Drawing::g_drawing;
    }

    Game::World *Initializer::world() const {
        return Game::g_world;
    }

    Event::EventManager *Initializer::event() const {
        return Event::g_event;
    }

    Sound::SoundManager *Initializer::sound() const {
        return Sound::g_sound;
    }
} // Init