#ifndef BOSCONIAN_COLLISION_H
#define BOSCONIAN_COLLISION_H

#include "SDL_rect.h"
#include "Hitbox.h"
#include "../Game/Projectile.h"

namespace Physics {

    class CollisionManager {
    public:

        /**
         * Checks if two SDL_Rectangles intersect.
         * \param rect1 The first rectangle.
         * \param rect2 The second rectangle.
         * \return True if the rectangles intersect, false otherwise.
         */
        static bool checkIntersect(Hitbox hitbox1, Hitbox hitbox2);
        static bool entityHit(Game::Projectile *projectile, Hitbox entityHitbox);
    };

} // Physics

#endif //BOSCONIAN_COLLISION_H
