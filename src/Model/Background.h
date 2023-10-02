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

    void updateStars(float deltaTime, const Vector2D& cameraCenter) {
        elapsedTime += deltaTime * 1000; // Convert deltaTime to milliseconds
        if (elapsedTime > randomizeDelay) {
            static bool bToggle = false;
            std::pair<int, int> starsToUpdate;
            int starsSize = stars.size();

            if (bToggle) {
                starsToUpdate.first = 0;
                starsToUpdate.second = starsSize / 2;
            } else {
                starsToUpdate.first = starsSize / 2;
                starsToUpdate.second = starsSize;
            }

            for (size_t i = starsToUpdate.first; i < starsToUpdate.second; i++) {
                auto& star = stars.at(i);

                star.randomizePosition();
                star.randomizeColor();
            }
            elapsedTime = 0;
            bToggle = !bToggle;
        }
    }

    std::vector<Star> getStars() const {
        return stars;
    }

};

#endif //BOSCONIAN_BACKGROUND_H
