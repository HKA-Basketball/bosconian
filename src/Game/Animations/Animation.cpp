#include "Animation.h"

void Animation::update(std::shared_ptr<Drawing::Texture> texture, const float deltaTime) {
    if (images.size() <= 0 || !animationStart)
        return;

    animationTime += deltaTime * 1000.f;

    float progress = animationTime / animationDuration;
    progress = std::clamp(progress, 0.f, 1.f);
    int imageIndex = static_cast<int>(progress * (images.size() - 1));

    texture->changeTexture(images[imageIndex], true, "spritesheet.png");

    if (animationTime >= animationDuration)
        animationEnd = true;
}