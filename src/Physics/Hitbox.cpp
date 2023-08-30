#include <stack>
#include "Hitbox.h"

namespace Physics {

    Utils::Vector2D Hitbox::getPosition() const {
        return position;
    }

    Utils::Vector2D Hitbox::getSize() const {
        return size;
    }

    float Hitbox::getAngle() const {
        return angle;
    }

    void Hitbox::updatePosition(Utils::Vector2D newPosition) {
        newPosition -= (size*0.5f);
        position = newPosition;
    }

    void Hitbox::updateSize(const Utils::Vector2D& newSize) {
        size = newSize;
    }

    void Hitbox::updateAngle(const float deg) {
        angle = deg;
    }

    Hitbox::operator SDL_Rect() const {
        return SDL_Rect{
                static_cast<int>(position.x),
                static_cast<int>(position.y),
                static_cast<int>(size.x),
                static_cast<int>(size.y)
        };
    }

    Hitbox::operator Drawing::SDL_Rotated_Rect() const {
        return Drawing::SDL_Rotated_Rect{
                static_cast<int>(position.x),
                static_cast<int>(position.y),
                static_cast<int>(size.x),
                static_cast<int>(size.y),
                angle
        };
    }
} // Game