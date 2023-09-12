#ifndef BOSCONIAN_HITBOX_H
#define BOSCONIAN_HITBOX_H

#include "../../includes.h"
#include "../Drawing/Graphics.h"

namespace Physics {

    /**
     * The Hitbox class represents a rectangular collision hitbox used for collision detection.
     */
    class Hitbox {
    private:
        Utils::Vector2D position;
        Utils::Vector2D size;
        float angle;

    public:
        /**
         * Constructs a Hitbox instance with the specified position and size.
         * \param position The position of the hitbox's top-left corner.
         * \param size The size (width and height) of the hitbox.
         */
        Hitbox(const Utils::Vector2D& position, const Utils::Vector2D& size) :
            position(position - (size*0.5f)), size(size), angle(0) {};

        Hitbox(const Utils::Vector2D& position, const Utils::Vector2D& size, float angle) :
            position(position - (size*0.5f)), size(size), angle(angle) {};

        Utils::Vector2D getPosition() const;

        Utils::Vector2D getSize() const;

        float getAngle() const;

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

        void updateAngle(float d);

        /**
         * Get a constant reference to the SDL_Rect representing the hitbox's position and size.
         * \return A constant reference to the SDL_Rect hitbox.
         */

        explicit operator SDL_Rect() const;

        explicit operator Drawing::SDL_Rotated_Rect() const;
    };

} // namespace Physics

#endif //BOSCONIAN_HITBOX_H
