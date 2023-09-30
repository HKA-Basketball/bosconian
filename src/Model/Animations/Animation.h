#ifndef BOSCONIAN_ANIMATION_H
#define BOSCONIAN_ANIMATION_H

#include <vector>
#include "../../Graphic/SpriteInfo.h"

class Animation {
private:
    std::vector<SpriteInfo> sprites;  // List of sprites (frames) for the animation
    float animationSpeed{0.1};  // Time (in seconds) each sprite is shown for
    float elapsedTimeSinceLastFrame{0.0f};     // Time passed since the start of the animation
    bool isPlaying{false};        // Whether the animation is currently playing
    size_t currentFrame{0};   // The index of the current sprite being shown

public:
    Animation(const std::vector<SpriteInfo>& sprites) : sprites(sprites) {}

    void start() {
        elapsedTimeSinceLastFrame = 0.0f;
        currentFrame = 0;
        isPlaying = true;
    }

    void update(float deltaTime) {
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

    SpriteInfo getCurrentSprite() {
        if (currentFrame < sprites.size()) {
            return sprites.at(currentFrame);
        }
        return sprites.back();
    }

    bool isDone() const {
        return !isPlaying;
    }
};


#endif //BOSCONIAN_ANIMATION_H
