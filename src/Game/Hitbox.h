#ifndef BOSCONIAN_HITBOX_H
#define BOSCONIAN_HITBOX_H

#include "../../includes.h"

namespace Game {

    class Hitbox {
    private:
        SDL_Rect hitbox;
    public:
        Hitbox(Utils::Vector2D pos, Utils::Vector2D size);

        void updateHitboxPos(Utils::Vector2D newOrigin);

        const SDL_Rect &getHitbox() const;
    };

} // Game

#endif //BOSCONIAN_HITBOX_H
