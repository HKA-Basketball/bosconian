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

        Utils::Vector2D getPosition() const;

        Utils::Vector2D getSize() const;

        /**
         * Update the position of the hitbox by changing its origin.
         * \param newOrigin The new top-left corner position of the hitbox.
         */
        void updatePosition(Utils::Vector2D newPosition);

        /**
         * Update the size of the hitbox
         * \param newSize The new size of the hitbox.
         */
        void updateSize(const Utils::Vector2D& newSize);

        /**
         * Get a constant reference to the SDL_Rect representing the hitbox's position and size.
         * \return A constant reference to the SDL_Rect hitbox.
         */

        explicit operator SDL_Rect() const;
    };

} // Game

#endif //BOSCONIAN_HITBOX_H
