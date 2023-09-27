#include "Hitbox.h"

Vector2D Hitbox::getPosition() const {
    return position;
}

Vector2D Hitbox::getSize() const {
    return size;
}

const Degree Hitbox::getAngle() const {
    return angle;
}

void Hitbox::updatePosition(const Vector2D& newPosition) {
    position = newPosition;
}

void Hitbox::updateSize(const Vector2D& newSize) {
    size = newSize;
}

void Hitbox::updateAngle(const Degree newAngle) {
    angle = newAngle;
}

/*Hitbox::operator SDL_Rect() const {
    return SDL_Rect{
            static_cast<int>(position.x),
            static_cast<int>(position.y),
            static_cast<int>(size.x),
            static_cast<int>(size.y)
    };
}

Hitbox::operator SDL_Rotated_Rect() const {
    return SDL_Rotated_Rect{
            static_cast<int>(position.x),
            static_cast<int>(position.y),
            static_cast<int>(size.x),
            static_cast<int>(size.y),
            angle
    };
}*/