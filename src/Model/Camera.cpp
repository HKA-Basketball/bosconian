#include "Camera.h"

void Camera::centerOn(const Vector2D& newCenter) {
    this->center = newCenter;
}

Vector2D Camera::WorldToScreen(const Vector2D& worldPosition) const {
    return worldPosition - this->center + (size/2);
}

std::optional<Vector2D> Camera::IsInView(const Entity& entity) const {
    // Get the radius for camera and entity
    float cameraRadius = std::fmax(size.x, size.y) / 1.25f;

    SpriteInfo spriteInfo = entity.getSpriteInfo();
    SDL_Rect rect = spriteMap.at(spriteInfo);
    float entityRadius = std::max(rect.w, rect.h) / 1.25f;

    // Get the center position of the camera
    Vector2D cameraCenter = center;

    // Get the center position of the entity
    WrappedPositions positionsToCheck = entity.getWrappedPositions();

    // Check for collisions with the entity's original and wrapped positions
    for (const auto& position : positionsToCheck) {
        float distance = (cameraCenter - position).length();
        if (distance < (cameraRadius + entityRadius)) {
            return position; // Return the position where the entity is in view
        }
    }

    return std::nullopt; // Return std::nullopt when the entity is not in view
}