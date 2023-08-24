#ifndef BOSCONIAN_HITBOX_H
#define BOSCONIAN_HITBOX_H

#include "../../includes.h"

namespace Physics {

    /**
     * The Hitbox class represents a rectangular collision hitbox used for collision detection.
     */
    class Hitbox {
    private:
        Utils::Vector2D position;
        Utils::Vector2D size;

    public:
        /**
         * Constructs a Hitbox instance with the specified position and size.
         * \param position The position of the hitbox's top-left corner.
         * \param size The size (width and height) of the hitbox.
         */
        Hitbox(Utils::Vector2D position, Utils::Vector2D size) : position(position - (size*0.5f)), size(size) {};

        /**
         * Update the position of the hitbox by changing its origin.
         * \param newOrigin The new top-left corner position of the hitbox.
         */
        void updatePosition(Utils::Vector2D newPosition);

        /**
         * Get a constant reference to the SDL_Rect representing the hitbox's position and size.
         * \return A constant reference to the SDL_Rect hitbox.
         */
        //const SDL_Rect &getHitbox() const;

        const Utils::Vector2D getPosition() const;

        const Utils::Vector2D getSize() const;

        operator SDL_Rect();
    };

} // Game

#endif //BOSCONIAN_HITBOX_H
