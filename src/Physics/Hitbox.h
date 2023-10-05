#ifndef BOSCONIAN_HITBOX_H
#define BOSCONIAN_HITBOX_H

#include "../Utilities/Vector2D.h"
#include "../Utilities/Degree.h"

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
    Vector2D position; ///< The position of the hitbox's center point.
    Vector2D size;     ///< The dimensions (width and height) of the hitbox.
    Degree angle;       ///< The rotation angle of the hitbox in degrees.

public:
    /**
     * @brief Constructs a Hitbox instance with the specified position and size.
     *
     * The constructor initializes a hitbox with the given coordinates and
     * having the specified dimensions.
     *
     * @param position A vector representing the initial center position of the hitbox.
     * @param size A vector representing the initial dimensions (width and height) of the hitbox.
     */
    Hitbox(const Vector2D& position, const Vector2D& size) : position(position), size(size), angle(0) {};

    /**
     * @brief Constructs a Hitbox instance with the specified position, size, and rotation angle.
     *
     * This constructor initializes a hitbox with the given coordinates,
     * having the specified dimensions, and rotated by the specified angle.
     *
     * @param position A vector representing the initial center position of the hitbox.
     * @param size A vector representing the initial dimensions (width and height) of the hitbox.
     * @param angle The initial rotation angle of the hitbox in degrees.
     */
    Hitbox(const Vector2D& position, const Vector2D& size, Degree angle) : position(position), size(size), angle(angle) {};

    /**
     * @brief Gets the current position of the hitbox.
     * @return A vector representing the current center position of the hitbox.
     */
    Vector2D getPosition() const;

    /**
     * @brief Gets the current dimensions (width and height) of the hitbox.
     * @return A vector representing the current dimensions of the hitbox.
     */
    Vector2D getSize() const;

    /**
     * @brief Gets the current rotation angle of the hitbox.
     * @return The current rotation angle of the hitbox in degrees.
     */
    const Degree getAngle() const;

    /**
     * @brief Updates the position of the hitbox.
     *
     * This method sets a new center position for the hitbox, effectively moving it to a new location.
     *
     * @param newPosition A vector representing the new center position for the hitbox.
     */
    void updatePosition(const Vector2D& newPosition);

    /**
     * @brief Updates the dimensions (width and height) of the hitbox.
     *
     * This method sets new dimensions for the hitbox, effectively resizing it.
     *
     * @param newSize A vector representing the new dimensions for the hitbox.
     */
    void updateSize(const Vector2D& newSize);

    /**
     * @brief Updates the rotation angle of the hitbox.
     *
     * This method sets a new rotation angle for the hitbox, effectively rotating it.
     *
     * @param newAngle The new rotation angle for the hitbox in degrees.
     */
    void updateAngle(Degree newAngle);

    /**
     * @brief Casts the hitbox to an SDL_Rect structure.
     *
     * This method casts the hitbox to an SDL_Rect structure, which is used in the SDL library for
     * graphical manipulations. The SDL_Rect structure contains the top-left corner coordinates and the
     * dimensions of the rectangle.
     *
     * @return An SDL_Rect structure representing the hitbox.
     */
    //explicit operator SDL_Rect() const;

    /**
     * @brief Casts the hitbox to an SDL_Rotated_Rect structure.
     *
     * This method casts the hitbox to an SDL_Rotated_Rect structure, which represents a rectangle with
     * a specified rotation angle. This structure is used for graphical representations and manipulations
     * involving and extension of the rectangles in the SDL library that also holds information about rotation.
     *
     * @return An SDL_Rotated_Rect structure representing the hitbox.
     */
    //explicit operator SDL_Rotated_Rect() const;
};

#endif //BOSCONIAN_HITBOX_H
