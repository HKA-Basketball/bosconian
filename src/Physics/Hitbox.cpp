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