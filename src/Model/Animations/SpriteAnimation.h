#ifndef BOSCONIAN_SPRITEANIMATION_H
#define BOSCONIAN_SPRITEANIMATION_H

#include <vector>
#include "Animation.h"
#include "../../Graphic/SpriteInfo.h"

class SpriteAnimation : public Animation {
private:
    std::vector<SpriteInfo> sprites;  // List of sprites (frames) for the animation
    float animationSpeed{0.1f};  // Time (in seconds) each sprite is shown for
    float elapsedTimeSinceLastFrame{0.0f};     // Time passed since the start of the animation
    size_t currentFrame{0};   // The index of the current sprite being shown

public:
    SpriteAnimation(const std::vector<SpriteInfo>& sprites) : Animation(), sprites(sprites) {}

    void start() override {
        currentFrame = 0;
        Animation::start();
    }

    void update(float deltaTime) override {
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
};

#endif //BOSCONIAN_SPRITEANIMATION_H
