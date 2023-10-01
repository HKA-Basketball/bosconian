#ifndef BOSCONIAN_BACKGROUND_H
#define BOSCONIAN_BACKGROUND_H

#include "RenderEngine.h"
#include "../Model/Camera.h"
#include "../Utilities/Math.h"
#include "../Utilities/Config.h"
#include <SDL.h>
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

    void drawStars(SDL_Renderer* renderer) const {
        Vector2D cameraCenter = Camera::Instance()->getCenter();
        float parallaxFactor = Config::parallaxFactor; // Adjust this value to control the strength of the parallax effect
        for (const auto& star : stars) {
            // Calculate parallax effect for each star
            float parallaxX = fmod(star.rect.x - parallaxFactor * cameraCenter.x, Config::levelWidth * Config::parallaxFactor);
            if (parallaxX < 0) parallaxX += Config::levelWidth * Config::parallaxFactor;

            float parallaxY = fmod(star.rect.y - parallaxFactor * cameraCenter.y, Config::levelHeight * Config::parallaxFactor);
            if (parallaxY < 0) parallaxY += Config::levelHeight * Config::parallaxFactor;

            // Draw star with parallax effect
            SDL_SetRenderDrawColor(renderer, star.color.r, star.color.g, star.color.b, star.color.a);
            SDL_FRect parallaxRect = {parallaxX, parallaxY, star.rect.w, star.rect.h};
            SDL_RenderFillRectF(renderer, &parallaxRect);
        }
    }

};

#endif //BOSCONIAN_BACKGROUND_H
