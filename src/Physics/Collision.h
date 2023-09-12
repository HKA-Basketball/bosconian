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
    };

} // Physics

#endif //BOSCONIAN_COLLISION_H
