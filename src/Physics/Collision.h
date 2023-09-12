#ifndef BOSCONIAN_COLLISION_H
#define BOSCONIAN_COLLISION_H

#include "SDL_rect.h"
#include "Hitbox.h"
#include "../../includes.h"
#include "../Game/Projectile.h"

namespace Physics {

    class CollisionManager {
    public:

        /**
         * Check if the two hit boxes intersect
         * \param hitbox1 The first hitbox.
         * \param hitbox2 The second hitbox.
         * \return True if the hitboxes intersect, false otherwise.
         */
        static bool checkIntersect(Hitbox hitbox1, Hitbox hitbox2);
        static bool entityHit(Game::Projectile *projectile, Hitbox entityHitbox);

    private:

        // Helper function to project a polygon onto an axis.
        static void projectPolygon(const Hitbox& hitbox, const Utils::Vector2D& axis, float& min, float& max);

        // Helper function to check if two intervals overlap.
        static bool intervalsOverlap(float minA, float maxA, float minB, float maxB);
    };

} // Physics

#endif //BOSCONIAN_COLLISION_H
