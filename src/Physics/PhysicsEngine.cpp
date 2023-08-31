#include "PhysicsEngine.h"
#include <algorithm>

bool PhysicsEngine::checkOBBCollision(const Entity& a, const Entity& b) {
    // Get the vectors representing the OBB's axes
    std::vector<SDL_Point> axes{
            {a.getAxisX().x, a.getAxisX().y},
            {a.getAxisY().x, a.getAxisY().y},
            {b.getAxisX().x, b.getAxisX().y},
            {b.getAxisY().x, b.getAxisY().y}
    };

    for (const auto& axis : axes) {
        float t1Min = std::numeric_limits<float>::max();
        float t1Max = std::numeric_limits<float>::lowest();

        float t2Min = std::numeric_limits<float>::max();
        float t2Max = std::numeric_limits<float>::lowest();

        // Project all vertices of OBB a onto axis
        for (int i = 0; i < 4; ++i) {
            float dot = a.getVertex(i).x * axis.x + a.getVertex(i).y * axis.y;
            t1Min = std::min(t1Min, dot);
            t1Max = std::max(t1Max, dot);
        }

        // Project all vertices of OBB b onto axis
        for (int i = 0; i < 4; ++i) {
            float dot = b.getVertex(i).x * axis.x + b.getVertex(i).y * axis.y;
            t2Min = std::min(t2Min, dot);
            t2Max = std::max(t2Max, dot);
        }

        // Check if projections overlap
        if (!(t1Max >= t2Min && t1Min <= t2Max)) {
            return false; // No overlap found, so OBBs aren't colliding
        }
    }

    return true; // All projections overlap, so OBBs are colliding
}

void PhysicsEngine::resolveCollisions(std::vector<Entity>& entities) {
    for (size_t i = 0; i < entities.size(); ++i) {
        for (size_t j = i + 1; j < entities.size(); ++j) {
            if (checkOBBCollision(entities[i], entities[j])) {
                // Handle collision between entities[i] and entities[j]
                // This can be as simple as reversing their velocities, or more complex.
                // Modify the entities' properties as required.
            }
        }
    }
}
