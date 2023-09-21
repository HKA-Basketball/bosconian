#ifndef BOSCONIAN_WORLDMODEL_H
#define BOSCONIAN_WORLDMODEL_H

#include "../Utilities/GlobalVars.h"
#include "../Drawing/Graphics.h"
#include "../../includes.h"

namespace Game {

/**
 * The WorldModel class represents the data and logic of the world's background and elements.
 */
    class WorldModel {
    private:
        /** The elapsed time in ticks. */
        Uint64 elapsedTime;
        /** The delay between star updates in milliseconds. */
        const int starDelay = 500;
        /** The number of stars. */
        const int countStars = 210;
        /** The value of sine function. */
        float sineValue;
        /** Toggle flag for animation. */
        bool bToggle;
        /** Initialization flag. */
        bool bInit;
        /** Vector of pairs containing rectangles and colors for stars. */
        std::vector<std::pair<SDL_FRect, SDL_Color>> vcPoints;

    public:
        /**
         * Constructs a WorldModel instance.
         */
        WorldModel() {
            elapsedTime = 0;
            bToggle = false;
            bInit = false;
            vcPoints.resize(countStars * 2);
        }

        /**
         * Initializes the background elements.
         */
        void initBackground() {
            for (int i = 0; i < countStars * 2; i++) {
                vcPoints[i].first.x = Utils::Math::RandomFloat(0, Utils::GlobalVars::lvlWidth * 0.6f);
                vcPoints[i].first.y = Utils::Math::RandomFloat(0, Utils::GlobalVars::lvlHeight * 0.6f);
                vcPoints[i].first.h = vcPoints[i].first.w = Utils::Math::RandomFloat(0.5f, 5.5f);

                sineValue = sin(2.f * M_PI * (rand() % 1000) / 5.f);
                vcPoints[i].second.r = static_cast<Uint8>((sineValue + 1.f) / 2.f * 255.f);
                sineValue = sin(2.f * M_PI * (rand() % 1000) / 5.f);
                vcPoints[i].second.g = static_cast<Uint8>((sineValue + 1.f) / 2.f * 255.f);
                sineValue = sin(2.f * M_PI * (rand() % 1000) / 5.f);
                vcPoints[i].second.b = static_cast<Uint8>((sineValue + 1.f) / 2.f * 255.f);
                vcPoints[i].second.a = 255;
            }
            bInit = true;
        }

        /**
         * Updates the background elements based on the elapsed time.
         * \param deltaTime The time elapsed since the last update in seconds.
         */
        void updateBackground(float deltaTime) {
            elapsedTime += deltaTime * 1000.f;
            if (elapsedTime > starDelay) {
                if (!bToggle) {
                    for (int i = 0; i < countStars; i++) {
                        vcPoints[i].first.x = Utils::Math::RandomFloat(0, Utils::GlobalVars::lvlWidth * 0.6f);
                        vcPoints[i].first.y = Utils::Math::RandomFloat(0, Utils::GlobalVars::lvlHeight * 0.6f);
                        vcPoints[i].first.h = vcPoints[i].first.w = Utils::Math::RandomFloat(0.5f, 5.5f);

                        sineValue = sin(2.f * M_PI * (rand() % 1000) / 5.f);
                        vcPoints[i].second.r = static_cast<Uint8>((sineValue + 1.f) / 2.f * 255.f);
                        sineValue = sin(2.f * M_PI * (rand() % 1000) / 5.f);
                        vcPoints[i].second.g = static_cast<Uint8>((sineValue + 1.f) / 2.f * 255.f);
                        sineValue = sin(2.f * M_PI * (rand() % 1000) / 5.f);
                        vcPoints[i].second.b = static_cast<Uint8>((sineValue + 1.f) / 2.f * 255.f);
                        vcPoints[i].second.a = 255;
                    }
                    bToggle = true;
                } else if (bToggle) {
                    for (int i = countStars; i < countStars * 2; i++) {
                        vcPoints[i].first.x = Utils::Math::RandomFloat(0, Utils::GlobalVars::lvlWidth * 0.6f);
                        vcPoints[i].first.y = Utils::Math::RandomFloat(0, Utils::GlobalVars::lvlHeight * 0.6f);
                        vcPoints[i].first.h = vcPoints[i].first.w = Utils::Math::RandomFloat(0.5f, 5.5f);

                        sineValue = sin(2.f * M_PI * (rand() % 1000) / 5.f);
                        vcPoints[i].second.r = static_cast<Uint8>((sineValue + 1.f) / 2.f * 255.f);
                        sineValue = sin(2.f * M_PI * (rand() % 1000) / 5.f);
                        vcPoints[i].second.g = static_cast<Uint8>((sineValue + 1.f) / 2.f * 255.f);
                        sineValue = sin(2.f * M_PI * (rand() % 1000) / 5.f);
                        vcPoints[i].second.b = static_cast<Uint8>((sineValue + 1.f) / 2.f * 255.f);
                        vcPoints[i].second.a = 255;
                    }
                    bToggle = false;
                }
                elapsedTime -= starDelay;
            }
        }

        /**
         * Checks if the background elements have been initialized.
         * \return `true` if the background is initialized, otherwise `false`.
         */
        bool isInit() const {
            return bInit;
        }

        /**
         * Retrieves the vector of rectangles and colors representing stars.
         * \return A constant reference to the vector of star information.
         */
        const std::vector<std::pair<SDL_FRect, SDL_Color>> &getVcPoints() const {
            return vcPoints;
        }
    };
}
#endif //BOSCONIAN_WORLDMODEL_H
