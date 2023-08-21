#ifndef BOSCONIAN_HITBOX_H
#define BOSCONIAN_HITBOX_H

#include "../../includes.h"

namespace Game {

    /**
     * The Hitbox class represents a rectangular collision hitbox used for collision detection.
     */
    class Hitbox {
    private:
        /** The SDL_Rect representing the position and size of the hitbox. */
        SDL_Rect hitbox;

    public:
        /**
         * Constructs a Hitbox instance with the specified position and size.
         * \param pos The position of the hitbox's top-left corner.
         * \param size The size (width and height) of the hitbox.
         */
        Hitbox(Utils::Vector2D pos, Utils::Vector2D size);

        /**
         * Update the position of the hitbox by changing its origin.
         * \param newOrigin The new top-left corner position of the hitbox.
         */
        void updateHitboxPos(Utils::Vector2D newOrigin);

        /**
         * Get a constant reference to the SDL_Rect representing the hitbox's position and size.
         * \return A constant reference to the SDL_Rect hitbox.
         */
        const SDL_Rect &getHitbox() const;
    };

} // Game

#endif //BOSCONIAN_HITBOX_H
