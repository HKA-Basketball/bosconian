#ifndef BOSCONIAN_COLLISION_H
#define BOSCONIAN_COLLISION_H

#include "SDL_rect.h"
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
        static bool checkIntersect(SDL_Rect hitbox1, SDL_Rect hitbox2);
        static bool entityHit(Game::Projectile *projectile, SDL_Rect entityHitbox);
    };

} // Physics

#endif //BOSCONIAN_COLLISION_H
