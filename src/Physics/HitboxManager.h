#ifndef BOSCONIAN_HITBOXMANAGER_H
#define BOSCONIAN_HITBOXMANAGER_H

#include <array>

#include "Hitbox.h"

/**
 * @class HitboxManager
 * @brief Manages collision detection between hitboxes.
 *
 * The HitboxManager provides utility functions to facilitate collision
 * detection between rectangular hitboxes in 2D space. It offers methods
 * for determining if two hitboxes are colliding, projecting hitbox corners
 * onto an axis, and calculating corners of a given hitbox. This class
 * plays a fundamental role in ensuring accurate and efficient collision
 * detection in a game or graphical application.
 */
class HitboxManager {
public:
    /**
     * @brief Determines if two hitboxes are colliding.
     *
     * This function checks for overlap between two provided hitboxes
     * and returns true if there is a collision or overlap.
     *
     * @param box1 The first hitbox.
     * @param box2 The second hitbox.
     * @return true if the hitboxes are colliding, false otherwise.
     */
    static bool areColliding(const Hitbox& box1, const Hitbox& box2);

private:
    /// Represents the corners of a hitbox using a fixed-size array of Vector2D objects.
    typedef std::array<Vector2D, 4> Corners;

    /**
     * @brief Determines if two intervals on a line are overlapping.
     *
     * Given the minimum and maximum values of two intervals (A and B),
     * this function checks if they overlap.
     *
     * @param minA Minimum value of interval A.
     * @param maxA Maximum value of interval A.
     * @param minB Minimum value of interval B.
     * @param maxB Maximum value of interval B.
     * @return true if the intervals overlap, false otherwise.
     */
    static bool areIntervalsOverlapping(float minA, float maxA, float minB, float maxB);

    /**
     * @brief Calculates the corners of a given hitbox.
     *
     * This function determines the four corners of a hitbox based on its
     * attributes and returns them in a Corners array.
     *
     * @param box The hitbox for which corners are to be determined.
     * @return A Corners array representing the four corners of the hitbox.
     */
    static Corners getCorners(const Hitbox &box);

    /**
     * @brief Projects the hitbox corners onto a given axis.
     *
     * By projecting the hitbox corners onto an axis, this function assists
     * in determining overlaps between hitboxes during collision detection.
     *
     * @param corners The corners of the hitbox to project.
     * @param axis The axis onto which the hitbox corners should be projected.
     * @return A Vector2D representing the projected shape on the axis.
     */
    static Vector2D projectOntoAxis(const Corners &corners, const Vector2D &axis);
};

#endif //BOSCONIAN_HITBOXMANAGER_H
