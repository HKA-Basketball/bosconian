#include <stack>
#include "Hitbox.h"

namespace Game {
    Hitbox::Hitbox(Utils::Vector2D pos, Utils::Vector2D size) {
        pos -= (size*0.5f);

        hitbox.x = pos.x;
        hitbox.y = pos.y;
        hitbox.w = size.x;
        hitbox.h = size.x;
    }

    const SDL_Rect &Hitbox::getHitbox() const {
        return hitbox;
    }

    void Hitbox::updateHitboxPos(Utils::Vector2D newOrigin) {
        newOrigin -= (Utils::Vector2D(hitbox.w, hitbox.h)*0.5f);
        hitbox.x = newOrigin.x;
        hitbox.y = newOrigin.y;
    }
} // Game