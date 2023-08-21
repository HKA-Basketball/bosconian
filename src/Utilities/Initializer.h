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

    /**
     * \class Initializer
     * \brief A singleton class responsible for initializing and managing game objects.
     */
    class Initializer {
    private:
        Renderer::Window* g_window;

        static Initializer* instance;
        Initializer() {}
        bool isInit = false;
    public:
        /**
         * Get the singleton instance of the Initializer class.
         * \return A pointer to the Initializer instance.
         */
        static Initializer* getInstance() {
            if (instance == nullptr) {
                instance = new Initializer();
            }
            return instance;
        }

        /**
         * Destructor that cleans up the allocated resources.
         * Deletes and sets pointers to nullptr for various game objects.
         */
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

        /**
         * Initialize the game objects.
         * \return True if initialization was successful, false otherwise.
         */
        bool initGameObjs();

        /**
         * Get a pointer to the game window.
         * \return A pointer to the game window.
         */
        Renderer::Window *window() const;

        /**
         * Get a pointer to the renderer.
         * \return A pointer to the renderer.
         */
        Renderer::RendererSDL *renderer() const;

        /**
         * Get a pointer to the graphics drawing object.
         * \return A pointer to the graphics drawing object.
         */
        Drawing::Graphics *drawing() const;

        /**
         * Get a pointer to the game world object.
         * \return A pointer to the game world object.
         */
        Game::World *world() const;

        /**
         * Get a pointer to the event manager object.
         * \return A pointer to the event manager object.
         */
        Event::EventManager *event() const;

        /**
         * Get a pointer to the sound manager object.
         * \return A pointer to the sound manager object.
         */
        Sound::SoundManager *sound() const;

    };

} // Init

#endif //BOSCONIAN_INITIALIZER_H
