#include "HitboxManager.h"

#include <vector>
#include <array>

// Define a Corners type for convenience.
typedef std::array<Vector2D, 4> Corners;

bool HitboxManager::areColliding(const Hitbox& box1, const Hitbox& box2) {
    // Calculate the four corners of each hitbox
    Corners cornersA = getCorners(box1);
    Corners cornersB = getCorners(box2);

    // Define the axes based on the edges of the hitboxes. These axes will be used
    // for the Separating Axis Theorem (SAT) collision detection.
    Corners axes = {
        (cornersA[1] - cornersA[0]).normalized(),
        (cornersA[3] - cornersA[0]).normalized(),
        (cornersB[1] - cornersB[0]).normalized(),
        (cornersB[3] - cornersB[0]).normalized()
    };

    // Test each axis to see if the hitboxes are separated along that axis.
    for (const Vector2D& axis : axes) {
        auto projectionA = projectOntoAxis(cornersA, axis);
        auto projectionB = projectOntoAxis(cornersB, axis);

        // If projections don't overlap, hitboxes are not colliding on this axis.
        if (!areIntervalsOverlapping(projectionA.x, projectionA.y, projectionB.x, projectionB.y)) {
            return false;
        }
    }

    // All projections overlapped; hitboxes are colliding.
    return true;
}

bool HitboxManager::areIntervalsOverlapping(float minA, float maxA, float minB, float maxB) {
    // Check if interval [minA, maxA] overlaps with interval [minB, maxB]
    return minB <= maxA && minA <= maxB;
}

Corners HitboxManager::getCorners(const Hitbox& box) {
    // Calculate half dimensions for convenience
    float halfWidth = box.getSize().x * 0.5f;
    float halfHeight = box.getSize().y * 0.5f;

    // Define the four corners relative to an unrotated hitbox
    Corners corners = {
        Vector2D(-halfWidth, -halfHeight),
        Vector2D(halfWidth, -halfHeight),
        Vector2D(halfWidth, halfHeight),
        Vector2D(-halfWidth, halfHeight)
    };

    // Rotate each vertex by the box's rotation angle and then translate it to the box's position
    float radAngle = box.getAngle().toRadians();
    for (Vector2D& corner : corners) {
        corner = corner.rotate(radAngle) + box.getPosition() + Vector2D(halfWidth, halfHeight);
    }

    return corners;
}

Vector2D HitboxManager::projectOntoAxis(const Corners& corners, const Vector2D& axis) {
    // Calculate the projection of the first corner on the axis
    float min = axis.dot(corners[0]);
    float max = min;

    // Iterate over the remaining corners
    for (int i = 1; i < 4; ++i) {
        float projection = axis.dot(corners[i]);

        // Update the min and max values
        if (projection < min) min = projection;
        if (projection > max) max = projection;
    }

    // Return the min and max projection values as a 2D vector
    return {min, max};
}
