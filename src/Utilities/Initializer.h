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

namespace Initialization {

    class Initializer {
    private:
        Renderer::Window* g_window;
        Renderer::RendererSDL* g_renderer;
        Drawing::Graphics* g_drawing;
        Game::World* g_world;
        Event::EventManager* g_event;
        Sound::SoundManager* g_sound;


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
            delete g_renderer;
            delete g_drawing;
            delete g_world;
            delete g_event;
            delete g_sound;

            // Set the pointers to nullptr
            g_window = nullptr;
            g_renderer = nullptr;
            g_drawing = nullptr;
            g_world = nullptr;
            g_event = nullptr;
            g_sound = nullptr;
        }

        bool initGameObjs();

        Renderer::Window *window() const;
        Renderer::RendererSDL *renderer() const;
        Drawing::Graphics *drawing() const;
        Game::World *world() const;
        Event::EventManager *event() const;
        Sound::SoundManager *sound() const;

    };

} // Initialization

#endif //BOSCONIAN_INITIALIZER_H
