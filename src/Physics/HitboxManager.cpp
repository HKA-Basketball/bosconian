#include "HitboxManager.h"
#include <cmath>
#include <vector>

bool HitboxManager::areColliding(const Hitbox& box1, const Hitbox& box2) {
    auto position1 = box1.getPosition();
    auto size1 = box1.getSize();
    auto position2 = box2.getPosition();
    auto size2 = box2.getSize();

    if (position1.x + size1.x < position2.x ||
        position2.x + size2.x < position1.x) {
        return false; // No horizontal overlap
    }

    if (position1.y + size1.y < position2.y ||
        position2.y + size2.y < position1.y) {
        return false; // No vertical overlap
    }

    return true; // Intersection

    // Retrieve position, size, and angle for both hitboxes
    //Vector2D position1 = box1.getPosition();
    //Vector2D size1 = box1.getSize();
    float angle1 = box1.getAngle().getDegree();

    //Vector2D position2 = box2.getPosition();
    //Vector2D size2 = box2.getSize();
    float angle2 = box2.getAngle().getDegree();

    // Compute the four axes (normalized) to test against, for both OBBs
    std::vector<Vector2D> axes{
            {std::cos(angle1), std::sin(angle1)},
            {-std::sin(angle1), std::cos(angle1)},
            {std::cos(angle2), std::sin(angle2)},
            {-std::sin(angle2), std::cos(angle2)}
    };

    // For each axis...
    for (const auto& axis : axes) {
        // Project both OBBs onto the axis
        float proj1 = projectOntoAxis(box1, axis);
        float proj2 = projectOntoAxis(box2, axis);

        // Check for non-overlapping projections, which means a separation along this axis exists, and thus, no collision
        if (proj1 < proj2 || proj2 < proj1) {
            return false;
        }
    }

    // No separating axis found, the OBBs are colliding
    return true;
}

float HitboxManager::projectOntoAxis(const Hitbox& box, const Vector2D& axis) {
    // Retrieve position, size, and angle of the box
    Vector2D position = box.getPosition();
    Vector2D size = box.getSize();
    float angle = box.getAngle().getDegree();

    // Compute the half extents of the OBB along each of its local axes
    Vector2D halfExtents = size * 0.5f;

    // Calculate the four vertices of the OBB
    std::vector<Vector2D> vertices {
            position + Vector2D(cos(angle), sin(angle)) * halfExtents.x + Vector2D(-sin(angle), cos(angle)) * halfExtents.y,
            position - Vector2D(cos(angle), sin(angle)) * halfExtents.x + Vector2D(-sin(angle), cos(angle)) * halfExtents.y,
            position - Vector2D(cos(angle), sin(angle)) * halfExtents.x - Vector2D(-sin(angle), cos(angle)) * halfExtents.y,
            position + Vector2D(cos(angle), sin(angle)) * halfExtents.x + Vector2D(-sin(angle), cos(angle)) * halfExtents.y,
    };

    // Project each vertex onto the axis and find the min and max of those projections
    float minProj = axis.dot(vertices[0]);
    float maxProj = minProj;
    for (const auto& vertex : vertices) {
        float proj = axis.dot(vertex);
        minProj = std::min(minProj, proj);
        maxProj = std::max(maxProj, proj);
    }

    // Return the minimum projection (or maximum, depending on the requirement, possibly as a pair)
    return minProj;
}