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
         * Check if the two oriented bounding boxes intersect
         * \param rect1 The first obb.
         * \param rect2 The second obb.
         * \return True if the obb's intersect, false otherwise.
         */
        static bool checkIntersect(Hitbox hitbox1, Hitbox hitbox2);
        static bool entityHit(Game::Projectile *projectile, Hitbox entityHitbox);
    };

} // Physics

#endif //BOSCONIAN_COLLISION_H
