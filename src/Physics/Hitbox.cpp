#include <stack>
#include "Hitbox.h"

namespace Physics {

    const Utils::Vector2D Hitbox::getPosition() const {
        return position;
    }

    const Utils::Vector2D Hitbox::getSize() const {
        return size;
    }

    void Hitbox::updatePosition(Utils::Vector2D newPosition) {
        newPosition -= (size*0.5f);
        position = newPosition;
    }

    Hitbox::operator SDL_Rect() {
        return SDL_Rect{
                static_cast<int>(position.x),
                static_cast<int>(position.y),
                static_cast<int>(size.x),
                static_cast<int>(size.y)
        };
    }
} // Game