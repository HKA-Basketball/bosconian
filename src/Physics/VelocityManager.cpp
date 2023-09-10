#include "VelocityManager.h"
#include <cmath>

void VelocityManager::updateVelocity(Vec2& position, Degree angle, float speed, float deltaTime) {
    position.x += speed * cos(angle.toRadians()) * deltaTime;
    position.y += speed * sin(angle.toRadians()) * deltaTime;
}

Vec2 VelocityManager::getNewPosition(const Vec2& position, Degree angle, float speed, float deltaTime) {
    Vec2 newPosition;
    newPosition.x = position.x + speed * cos(angle.toRadians()) * deltaTime;
    newPosition.y = position.y + speed * sin(angle.toRadians()) * deltaTime;
    return newPosition;
}
