#ifndef BOSCONIAN_WORLD_H
#define BOSCONIAN_WORLD_H

#include "WorldModel.h"
#include "WorldView.h"

#include "../../includes.h"
#include "../Utilities/GlobalVars.h"

namespace Game {

    /**
     * The World class manages the world's data and rendering.
     */
    class World {
    private:
        /** The WorldModel instance. */
        WorldModel m_model;
        /** The WorldView instance. */
        WorldView m_view;

    public:
        /**
         * Constructs a World instance with a default WorldModel and WorldView.
         */
        World() : m_model(), m_view(m_model)
        {}

        /**
         * Updates the world's elements based on the elapsed time.
         * \param deltaTime The time elapsed since the last update in seconds.
         */
        void update(float deltaTime) {
            m_model.updateBackground(deltaTime);
        }

        /**
         * Renders the background elements.
         */
        void renderBackground() {
            if (!m_view.drawBackground()) {
                m_model.initBackground();
            }
        }

        /**
         * Renders a 2D radar display on the screen.
         * \param pos The position of the radar display.
         * \param size The size of the radar display.
         * \param baseShips A vector of base ship positions.
         */
        void render2DRadar(Utils::Vector2D pos, Utils::Vector2D size, std::vector<Utils::Vector2D> baseShips) {
            m_view.draw2DRadar(pos, size, baseShips);
        }
    }; extern World* g_world;

} // Game

#endif //BOSCONIAN_WORLD_H
