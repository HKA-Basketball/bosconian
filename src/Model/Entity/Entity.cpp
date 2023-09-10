#include "Entity.h"
#include "../../Physics/VelocityManager.h"

Entity::Entity(SDL_Texture* texture)
        : texture(texture), speed(0.0f), angle(0.0f) {
    // Initialize other member variables as needed
}

Entity::~Entity() {
    // Any cleanup if necessary
}

void Entity::Update(float deltaTime) {
    // Updating position
    this->position.x += this->speed * std::cos(this->angle.toRadians()) * deltaTime;
    this->position.y += this->speed * std::sin(this->angle.toRadians()) * deltaTime;
    VelocityManager::updateVelocity(this->position, this->angle, this->speed, deltaTime);
}

SDL_Rect Entity::getSpriteClip() const {
    return this->spriteClip;
}

void Entity::setSpriteClip(const SDL_Rect clip) {
    this->spriteClip = clip;
}

void Entity::setPosition(const Vec2& newPosition) {
    this->position = newPosition;
}

Vec2 Entity::getPosition() const {
    return this->position;
}

void Entity::setSpeed(const float newSpeed) {
    this->speed = newSpeed;
}

float Entity::getSpeed() const {
    return this->speed;
}

void Entity::setAngle(const float newAngle) {
    this->angle.setDegree(newAngle);
}

void Entity::setAngle(const Degree newAngle) {
    this->angle = newAngle;
}

Degree Entity::getAngle() const {
    return this->angle;
}
