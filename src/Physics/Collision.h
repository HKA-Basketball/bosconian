#ifndef BOSCONIAN_COLLISION_H
#define BOSCONIAN_COLLISION_H

#include "SDL_rect.h"
#include "Hitbox.h"
#include "../../includes.h"
#include "../Game/Projectile.h"

namespace Physics {

    /**
     * @class CollisionManager
     * @brief Manages collision detection functionalities for the game.
     *
     * The CollisionManager class is responsible for handling collision detection
     * functionalities, which include checking the intersection of two hitboxes and
     * determining if a projectile hits an entity hitbox.
     */
    class CollisionManager {
    public:

        /**
         * @brief Check if two hitboxes intersect.
         *
         * This method checks whether two hitboxes intersect using either axis-aligned
         * bounding box (AABB) collision detection or oriented bounding box (OBB)
         * collision detection based on the collision mode set in Utils::GlobalVars.
         *
         * @param hitbox1 The first hitbox to check.
         * @param hitbox2 The second hitbox to check.
         * @return True if the hitboxes intersect, false otherwise.
         */
        static bool checkIntersect(Hitbox hitbox1, Hitbox hitbox2);

        /**
         * @brief Check if a projectile hits an entity hitbox.
         *
         * This method determines whether a projectile, which is active, collides
         * with an entity hitbox.
         *
         * @param projectile A pointer to the projectile to check.
         * @param entityHitbox The entity hitbox to check against.
         * @return True if the active projectile hits the entity hitbox, false otherwise.
         */
        static bool entityHit(Game::Projectile *projectile, Hitbox entityHitbox);

    private:
        // Helper function to project a polygon onto an axis.
        static void projectPolygon(const Hitbox& hitbox, const Utils::Vector2D& axis, float& min, float& max);

        // Helper function to check if two intervals overlap.
        static bool intervalsOverlap(float minA, float maxA, float minB, float maxB);
    };

} // namespace Physics

#endif //BOSCONIAN_COLLISION_H