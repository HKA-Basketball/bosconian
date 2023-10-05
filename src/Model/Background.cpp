#include "Background.h"

Star::Star() {
    randomizePosition();
    randomizeSize();
    randomizeColor();
}

void Star::randomizePosition() {
    rect.x = Random::randomFloat(0, Config::levelWidth * Config::parallaxFactor); // 3000 * 0.6f
    rect.y = Random::randomFloat(0, Config::levelHeight * Config::parallaxFactor); // 4000 * 0.6f
}

void Star::randomizeSize() {
    rect.w = rect.h = Random::randomFloat(0.5f, 5.5f);
}

void Star::randomizeColor() {
    color.r = Random::randomInt(0, 255);
    color.g = Random::randomInt(0, 255);
    color.b = Random::randomInt(0, 255);
    color.a = Random::randomInt(0, 255);
}

Background::Background() {
    stars.resize(numStars);
}

void Background::update(float deltaTime) {
    elapsedTime += deltaTime * 1000; // Convert deltaTime to milliseconds
    if (elapsedTime > randomizeDelay) {
        int starsSize = stars.size();
        int starBegin = starHalfToggle ? 0 : starsSize / 2;
        int starEnd = starHalfToggle ? starsSize / 2 : starsSize;

        for (size_t i = starBegin; i < starEnd; i++) {
            auto& star = stars.at(i);

            star.randomizePosition();
            star.randomizeColor();
        }

        elapsedTime = 0;
        starHalfToggle = !starHalfToggle;
    }
}

std::vector<Star> Background::getStars() const {
    return stars;
}