#include "Collision.h"

namespace Physics {

    // Check if the bounding boxes of the two intersect
    bool CollisionManager::checkIntersect(const Hitbox hitbox1, const Hitbox hitbox2) {
        auto position1 = hitbox1.getPosition();
        auto size1 = hitbox1.getSize();
        auto position2 = hitbox2.getPosition();
        auto size2 = hitbox2.getSize();

        if (position1.x + size1.x < position2.x ||
                position2.x + size2.x < position1.x) {
            return false; // No horizontal overlap
        }

        if (position1.y + size1.y < position2.y ||
                position2.y + size2.y < position1.y) {
            return false; // No vertical overlap
        }

        return true; // Intersection
    }

    bool CollisionManager::entityHit(Game::Projectile *projectile, const Hitbox entityHitbox) {
        if (!projectile->getActive())
            return false;

        if (checkIntersect(projectile->getHitbox(), entityHitbox))
            return true;

        return false;
    }
} // Physics