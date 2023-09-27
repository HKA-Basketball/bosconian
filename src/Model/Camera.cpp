#include "Camera.h"

// Define the instance pointer
Camera* Camera::instance = nullptr;

void Camera::centerOn(const Vector2D& newCenter) {
    this->center = newCenter;
}

Vector2D Camera::WorldToScreen(const Vector2D& worldPosition) const {
    return worldPosition - this->center + (size/2);
}

bool Camera::IsInView(const Entity& entity) const {
    /* TODO */
    /*Vector2D screenPosition = WorldToScreen(entity.position);
    return screenPosition.x >= 0 && screenPosition.x <= this->size.x &&
           screenPosition.y >= 0 && screenPosition.y <= this->size.y;*/
    return false;
}