#ifndef BOSCONIAN_HITBOX_H
#define BOSCONIAN_HITBOX_H

#include "../../includes.h"
#include "../Drawing/Graphics.h"

namespace Physics {

    /**
     * @class Hitbox
     * @brief Represents a rectangular collision hitbox used for collision detection in the physics engine.
     *
     * The Hitbox class encapsulates the attributes of a hitbox including its position, size, and angle.
     * It provides functionalities to update these attributes and to cast the hitbox to SDL structures
     * for graphical representation and manipulation.
     */
    class Hitbox {
    private:
        Utils::Vector2D position; ///< The position of the hitbox's center point.
        Utils::Vector2D size;     ///< The dimensions (width and height) of the hitbox.
        float angle;              ///< The rotation angle of the hitbox in degrees.

    public:
        /**
         * @brief Constructs a Hitbox instance with the specified position and size.
         *
         * The constructor initializes a hitbox with its center positioned at the given coordinates and
         * having the specified dimensions.
         *
         * @param position A vector representing the initial center position of the hitbox.
         * @param size A vector representing the initial dimensions (width and height) of the hitbox.
         */
        Hitbox(const Utils::Vector2D& position, const Utils::Vector2D& size) :
            position(position - (size*0.5f)), size(size), angle(0) {};

        /**
         * @brief Constructs a Hitbox instance with the specified position, size, and rotation angle.
         *
         * This constructor initializes a hitbox with its center positioned at the given coordinates,
         * having the specified dimensions, and rotated by the specified angle.
         *
         * @param position A vector representing the initial center position of the hitbox.
         * @param size A vector representing the initial dimensions (width and height) of the hitbox.
         * @param angle The initial rotation angle of the hitbox in degrees.
         */
        Hitbox(const Utils::Vector2D& position, const Utils::Vector2D& size, float angle) :
            position(position - (size*0.5f)), size(size), angle(angle) {};

        /**
         * @brief Gets the current center position of the hitbox.
         * @return A vector representing the current center position of the hitbox.
         */
        Utils::Vector2D getPosition() const;

        /**
         * @brief Gets the current dimensions (width and height) of the hitbox.
         * @return A vector representing the current dimensions of the hitbox.
         */
        Utils::Vector2D getSize() const;

        /**
         * @brief Gets the current rotation angle of the hitbox.
         * @return The current rotation angle of the hitbox in degrees.
         */
        float getAngle() const;

        /**
         * @brief Updates the center position of the hitbox.
         *
         * This method sets a new center position for the hitbox, effectively moving it to a new location.
         *
         * @param newPosition A vector representing the new center position for the hitbox.
         */
        void updatePosition(Utils::Vector2D newPosition);

        /**
         * @brief Updates the dimensions (width and height) of the hitbox.
         *
         * This method sets new dimensions for the hitbox, effectively resizing it.
         *
         * @param newSize A vector representing the new dimensions for the hitbox.
         */
        void updateSize(const Utils::Vector2D& newSize);

        /**
         * @brief Updates the rotation angle of the hitbox.
         *
         * This method sets a new rotation angle for the hitbox, effectively rotating it.
         *
         * @param newAngle The new rotation angle for the hitbox in degrees.
         */
        void updateAngle(float newAngle);

        /**
         * @brief Casts the hitbox to an SDL_Rect structure.
         *
         * This method casts the hitbox to an SDL_Rect structure, which is used in the SDL library for
         * graphical manipulations. The SDL_Rect structure contains the top-left corner coordinates and the
         * dimensions of the rectangle.
         *
         * @return An SDL_Rect structure representing the hitbox.
         */
        explicit operator SDL_Rect() const;

        /**
         * @brief Casts the hitbox to an SDL_Rotated_Rect structure.
         *
         * This method casts the hitbox to an SDL_Rotated_Rect structure, which represents a rectangle with
         * a specified rotation angle. This structure is used for graphical representations and manipulations
         * involving and extension of the rectangles in the SDL library that also holds information about rotation.
         *
         * @return An SDL_Rotated_Rect structure representing the hitbox.
         */
        explicit operator Drawing::SDL_Rotated_Rect() const;
    };

} // namespace Physics

#endif //BOSCONIAN_HITBOX_H
