#include "Camera.h"

// Define the instance pointer
Camera* Camera::instance = nullptr;

void Camera::centerOn(const Vector2D& newCenter) {
    this->center = newCenter;
}

Vector2D Camera::WorldToScreen(const Vector2D& worldPosition) const {
    return worldPosition - this->center + (size/2);
}

std::optional<Vector2D> Camera::IsInView(const Entity& entity) const {
    // Get the radius for camera and entity
    float cameraRadius = std::max(size.x, size.y) / 1.25f;

    SpriteInfo spriteInfo = entity.getSpriteInfo();
    SDL_Rect rect = spriteMap.at(spriteInfo);
    float entityRadius = std::max(rect.w, rect.h) / 1.25f;

    // Get the center position of the camera
    Vector2D cameraCenter = center;

    // Get the center position of the entity
    Vector2D entityCenter = entity.getPosition();

    // Check for collisions with the entity's original and wrapped positions
    std::vector<Vector2D> positionsToCheck = {
            entityCenter,
            entityCenter + Vector2D(Config::levelWidth, 0),
            entityCenter - Vector2D(Config::levelWidth, 0),
            entityCenter + Vector2D(0, Config::levelHeight),
            entityCenter - Vector2D(0, Config::levelHeight),
            entityCenter + Vector2D(Config::levelWidth, Config::levelHeight),
            entityCenter - Vector2D(Config::levelWidth, Config::levelHeight),
            entityCenter + Vector2D(Config::levelWidth, 0) - Vector2D(0, Config::levelHeight),
            entityCenter - Vector2D(Config::levelWidth, 0) + Vector2D(0, Config::levelHeight)
    };

    for (const auto& position : positionsToCheck) {
        float distance = (cameraCenter - position).length();
        if (distance < (cameraRadius + entityRadius)) {
            return position; // Return the position where the entity is in view
        }
    }

    return std::nullopt; // Return std::nullopt when the entity is not in view
}