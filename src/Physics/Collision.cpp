#include "Collision.h"

namespace Physics {

    // Check if the bounding boxes of the two intersect
    bool CollisionManager::checkIntersect(const SDL_Rect hitbox1, const SDL_Rect hitbox2) {
        if (hitbox1.x + hitbox1.w < hitbox2.x ||
                hitbox2.x + hitbox2.w < hitbox1.x) {
            return false; // No horizontal overlap
        }

        if (hitbox1.y + hitbox1.h < hitbox2.y ||
                hitbox2.y + hitbox2.h < hitbox1.y) {
            return false; // No vertical overlap
        }

        return true; // Intersection
    }

    bool CollisionManager::entityHit(Game::Projectile *projectile, SDL_Rect entityHitbox) {
        if (!projectile->getActive())
            return false;

        if (checkIntersect(projectile->getHitbox(), entityHitbox))
            return true;

        return false;
    }
} // Physics