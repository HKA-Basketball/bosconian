#include "SpriteAnimation.h"

SpriteAnimation::SpriteAnimation(const std::vector<SpriteInfo>& sprites) : Animation(), sprites(sprites) {}

void SpriteAnimation::start() {
    currentFrame = 0;
    Animation::start();
}

void SpriteAnimation::update(float deltaTime) {
    if (!isPlaying) {
        return;
    }

    elapsedTimeSinceLastFrame += deltaTime;
    if (elapsedTimeSinceLastFrame >= animationSpeed && currentFrame < sprites.size()) {
    elapsedTimeSinceLastFrame = 0.f;
    currentFrame++;
    }

    if (currentFrame == sprites.size()) {
    isPlaying = false;
    }
}

SpriteInfo SpriteAnimation::getCurrentSprite() {
    if (currentFrame < sprites.size()) {
        return sprites.at(currentFrame);
    }
    return sprites.back();
}