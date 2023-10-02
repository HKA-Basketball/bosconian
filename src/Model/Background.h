#ifndef BOSCONIAN_BACKGROUND_H
#define BOSCONIAN_BACKGROUND_H

#include "../View/RenderEngine.h"
#include "Camera.h"
#include "../Utilities/Math.h"
#include "../Utilities/Config.h"
#include "SDL.h"
#include <vector>

class Star {
public:
    SDL_FRect rect;
    SDL_Color color;

    Star() {
        randomizePosition();
        randomizeSize();
        randomizeColor();
    }

    void randomizePosition() {
        rect.x = Math::randomFloat(0, Config::levelWidth * Config::parallaxFactor); // 3000 * 0.6f
        rect.y = Math::randomFloat(0, Config::levelHeight * Config::parallaxFactor); // 4000 * 0.6f
    }

    void randomizeSize() {
        rect.w = rect.h = Math::randomFloat(0.5f, 5.5f);
    }

    void randomizeColor() {
        color.r = rand() % 256;
        color.g = rand() % 256;
        color.b = rand() % 256;
        color.a = rand() % 256;
    }
};

class Background {
private:
    static Background* instance;
    std::vector<Star> stars;
    const int numStars = 256;
    Uint64 elapsedTime = 0;
    const Uint64 randomizeDelay = 750; // 0,75 seconds in milliseconds
    bool starHalfToggle = false;

    Background() {
        stars.resize(numStars);
    }

public:
    static Background* Instance() {
        if (!instance) {
            instance = new Background();
        }
        return instance;
    }

    void update(float deltaTime) {
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

    std::vector<Star> getStars() const {
        return stars;
    }

};

#endif //BOSCONIAN_BACKGROUND_H
