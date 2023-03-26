#include "World.h"
#include "../Utilities/GlobalVars.h"
#include <cmath>

namespace Game {
    // TODO: move to Math
    float RandomFloat(float min, float max)
    {
        float random = ((float)rand()) / (float)RAND_MAX;

        float range = max - min;
        return (random * range) + min;
    }

    World::World(Drawing::Graphics *drawing) {
        g_drawing = drawing;
        LOG(std::string("World Successfully created"));
    }

    World::World(Drawing::Graphics* drawing, int width, int height) {
        g_drawing = drawing;
        // TODO:
        LOG(std::string("World Successfully created"));
    }

    bool World::initBackground() {
        oldTick = SDL_GetTicks64();
        starDelay = 500;
        countStars = 1000;
        bToggle = false;

        vcPoints.resize(countStars * 2);

        for (int i = 0; i < countStars * 2; i++)
        {
            vcPoints[i].first.x = RandomFloat(0, Utils::GlobalVars::lvlWidth + Utils::GlobalVars::windowWidth);
            vcPoints[i].first.y = RandomFloat(0, Utils::GlobalVars::lvlHeight + Utils::GlobalVars::windowHeight);
            vcPoints[i].first.h = vcPoints[i].first.w = RandomFloat(0.5f, 5.5f);

            sineValue = sin(2.f * M_PI * (rand() % 1000) / 5.f);
            vcPoints[i].second.r = static_cast<Uint8>((sineValue + 1.f) / 2.f * 255.f);
            sineValue = sin(2.f * M_PI * (rand() % 1000) / 5.f);
            vcPoints[i].second.g = static_cast<Uint8>((sineValue + 1.f) / 2.f * 255.f);
            sineValue = sin(2.f * M_PI * (rand() % 1000) / 5.f);
            vcPoints[i].second.b = static_cast<Uint8>((sineValue + 1.f) / 2.f * 255.f);
            vcPoints[i].second.a = 255;
        }

        return 1;
    }

    void World::runBackground(float offsetX, float offsetY) {
        if (SDL_GetTicks64() - oldTick > starDelay)
        {
            if (!bToggle)
            {
                for (int i = 0; i < countStars; i++)
                {
                    vcPoints[i].first.x = RandomFloat(0, Utils::GlobalVars::lvlWidth + Utils::GlobalVars::windowWidth);
                    vcPoints[i].first.y = RandomFloat(0, Utils::GlobalVars::lvlHeight + Utils::GlobalVars::windowHeight);
                    vcPoints[i].first.h = vcPoints[i].first.w = RandomFloat(0.5f, 5.5f);

                    sineValue = sin(2.f * M_PI * (rand() % 1000) / 5.f);
                    vcPoints[i].second.r = static_cast<Uint8>((sineValue + 1.f) / 2.f * 255.f);
                    sineValue = sin(2.f * M_PI * (rand() % 1000) / 5.f);
                    vcPoints[i].second.g = static_cast<Uint8>((sineValue + 1.f) / 2.f * 255.f);
                    sineValue = sin(2.f * M_PI * (rand() % 1000) / 5.f);
                    vcPoints[i].second.b = static_cast<Uint8>((sineValue + 1.f) / 2.f * 255.f);
                    vcPoints[i].second.a = 255;
                }
                bToggle = true;
            }
            else if (bToggle)
            {
                for (int i = countStars; i < countStars * 2; i++)
                {
                    vcPoints[i].first.x = RandomFloat(0, Utils::GlobalVars::lvlWidth + Utils::GlobalVars::windowWidth);
                    vcPoints[i].first.y = RandomFloat(0, Utils::GlobalVars::lvlHeight + Utils::GlobalVars::windowHeight);
                    vcPoints[i].first.h = vcPoints[i].first.w = RandomFloat(0.5f, 5.5f);

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

            oldTick = SDL_GetTicks64();
        }

        for (int i = 0; i < countStars * 2; i++)
        {
            SDL_FRect rec = { vcPoints[i].first.x - offsetX, vcPoints[i].first.y - offsetY, vcPoints[i].first.w, vcPoints[i].first.h };
            g_drawing->fillRectangle(vcPoints[i].second, rec);
        }
    }

    void World::draw2DRadar(Utils::Vector2D pos, Utils::Vector2D size, float offsetX, float offsetY,
                            Utils::Vector2D mapSize) {
        SDL_Rect rec = {(int)pos.x, (int)pos.y, (int)size.x + 8, (int)size.y + 8 };
        g_drawing->fillRectangle2({ 150, 0, 222, 255 }, rec);

        int scaled_x = pos.x + (offsetX / mapSize.x) * size.x;
        int scaled_y = pos.y + (offsetY / mapSize.y) * size.y;

        SDL_Rect recPos = { scaled_x, scaled_y, 8, 8 };
        g_drawing->fillRectangle2({ 255, 255, 255, 255 }, recPos);
    }
} // Game