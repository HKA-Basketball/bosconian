#ifndef BOSCONIAN_WORLD_H
#define BOSCONIAN_WORLD_H

#include "../../includes.h"
#include "../Drawing/Graphics.h"
#include "../Utilities/GlobalVars.h"

namespace Game {

    class WorldModel {
    private:
        Uint64 elapsedTicks;
        const int starDelay = 500;
        const int countStars = 210;
        float sineValue;
        bool bToggle;
        bool bInit;
        std::vector<std::pair<SDL_FRect, SDL_Color>> vcPoints;

    public:
        WorldModel() {
            elapsedTicks = 0;
            bToggle = false;
            bInit = false;
            vcPoints.resize(countStars * 2);
        }

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

        void updateBackground(float deltaTime) {
            elapsedTicks += deltaTime * 1000.f;
            if (elapsedTicks > starDelay) {
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
                elapsedTicks -= starDelay;
            }
        }

        bool isInit() const {
            return bInit;
        }

        const std::vector<std::pair<SDL_FRect, SDL_Color>> &getVcPoints() const {
            return vcPoints;
        }
    };

    class WorldView {
    private:
        Drawing::Graphics* g_drawing;
        const WorldModel& m_model;

    public:
        WorldView(Drawing::Graphics* drawing, const WorldModel& model)
            : g_drawing(drawing)
            , m_model(model)
        {}

        bool drawBackground() {
            if (!m_model.isInit())
                return 0;

            for (auto& point : m_model.getVcPoints()) {
                float x = fmod(point.first.x - Utils::GlobalVars::cameraPos.x * 0.6f, Utils::GlobalVars::lvlWidth * 0.6f);
                float y = fmod(point.first.y - Utils::GlobalVars::cameraPos.y * 0.6f, Utils::GlobalVars::lvlHeight * 0.6f);

                if (x < 0) x += Utils::GlobalVars::lvlWidth * 0.6f;
                if (y < 0) y += Utils::GlobalVars::lvlHeight * 0.6f;

                SDL_FRect rec = { x, y, point.first.w, point.first.h };
                g_drawing->fillRectangle(point.second, rec);
            }
            return 1;
        }

        void draw2DRadar(Utils::Vector2D pos, Utils::Vector2D size, std::vector<Utils::Vector2D> baseShips) {
            SDL_Rect rec = { (int)pos.x, (int)pos.y, (int)size.x, (int)size.y };
            g_drawing->fillRectangle2({ 150, 0, 222, 255 }, rec);

            int scaled_x = 0;
            int scaled_y = 0;

            for (auto& basePos : baseShips) {
                scaled_x = pos.x + (basePos.x / Utils::GlobalVars::lvlWidth) * (size.x - 10);
                scaled_y = pos.y + (basePos.y / Utils::GlobalVars::lvlHeight) * (size.y - 10);

                SDL_Rect recPos = { scaled_x, scaled_y, 10, 10 };
                g_drawing->fillRectangleOutline({ 0, 255, 0, 255 }, recPos);
            }

            scaled_x = pos.x + (Utils::GlobalVars::cameraPos.x / Utils::GlobalVars::lvlWidth) * (size.x - 8);
            scaled_y = pos.y + (Utils::GlobalVars::cameraPos.y / Utils::GlobalVars::lvlHeight) * (size.y - 8);

            SDL_Rect recPos = { scaled_x, scaled_y, 8, 8 };
            g_drawing->fillRectangle2({ 255, 255, 255, 255 }, recPos);
        }
    };

    class World {
    private:
        WorldModel m_model;
        WorldView m_view;

    public:
        World(Drawing::Graphics* drawing)
            : m_model()
            , m_view(drawing, m_model)
        {}

        void update(float deltaTime) {
            m_model.updateBackground(deltaTime);
        }

        void renderBackground() {
            if (!m_view.drawBackground()) {
                m_model.initBackground();
            }
        }

        void render2DRadar(Utils::Vector2D pos, Utils::Vector2D size, std::vector<Utils::Vector2D> baseShips) {
            m_view.draw2DRadar(pos, size, baseShips);
        }
    };

} // Game

#endif //BOSCONIAN_WORLD_H
