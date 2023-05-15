#include <stack>
#include "Hitbox.h"

namespace Game {
    Hitbox::Hitbox(Utils::Vector2D pos, Utils::Vector2D size) {
        hitbox.x = pos.x;
        hitbox.y = pos.y;
        hitbox.w = size.x;
        hitbox.h = size.x;
    }

    const SDL_Rect &Hitbox::getHitbox() const {
        return hitbox;
    }
} // Game