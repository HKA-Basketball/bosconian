#ifndef BOSCONIAN_INITIALIZER_H
#define BOSCONIAN_INITIALIZER_H

#include "../Utilities/Logging.h"
#include "../Utilities/GlobalVars.h"

#include "../Renderer/Window.h"
#include "../Renderer/Renderer.h"
#include "../Drawing/Graphics.h"
#include "../Event/EventManager.h"
#include "../Game/Entity.h"
#include "../Game/Hitbox.h"
#include "../Game/World.h"
#include "../Sound/SoundManager.h"

namespace Init {

    class Initializer {
    private:
        Renderer::Window* g_window;

        static Initializer* instance;
        Initializer() {}
        bool isInit = false;
    public:
        static Initializer* getInstance() {
            if (instance == nullptr) {
                instance = new Initializer();
            }
            return instance;
        }

        ~Initializer() {
            // Clean up the pointers
            delete g_window;
            delete Renderer::g_renderer;
            delete Drawing::g_drawing;
            delete Game::g_world;
            delete Event::g_event;
            delete Sound::g_sound;

            // Set the pointers to nullptr
            g_window = nullptr;
            Renderer::g_renderer = nullptr;
            Drawing::g_drawing = nullptr;
            Game::g_world = nullptr;
            Event::g_event = nullptr;
            Sound::g_sound = nullptr;
        }

        bool initGameObjs();

        Renderer::Window *window() const;
        Renderer::RendererSDL *renderer() const;
        Drawing::Graphics *drawing() const;
        Game::World *world() const;
        Event::EventManager *event() const;
        Sound::SoundManager *sound() const;

    };

} // Init

#endif //BOSCONIAN_INITIALIZER_H
