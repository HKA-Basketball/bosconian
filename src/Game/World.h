#ifndef BOSCONIAN_WORLD_H
#define BOSCONIAN_WORLD_H

#include "../../includes.h"
#include "../Drawing/Graphics.h"
#include "../Utilities/GlobalVars.h"

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

    /**
     * The WorldView class handles the rendering of the world's visual elements.
     */
    class WorldView {
    private:
        /** The drawing graphics interface. */
        Drawing::Graphics* g_drawing;
        /** A reference to the WorldModel. */
        const WorldModel& m_model;

    public:
        /**
         * Constructs a WorldView instance with the specified drawing graphics and WorldModel.
         * \param drawing The drawing graphics interface to use.
         * \param model A constant reference to the WorldModel instance.
         */
        WorldView(Drawing::Graphics* drawing, const WorldModel& model)
            : g_drawing(drawing)
            , m_model(model)
        {}

        /**
         * Draws the background elements if the world is initialized.
         * \return `true` if background was drawn, otherwise `false`.
         */
        bool drawBackground() {
            if (!m_model.isInit() || !g_drawing)
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

        /**
         * Draws a 2D radar display on the screen.
         * \param pos The position of the radar display.
         * \param size The size of the radar display.
         * \param baseShips A vector of base ship positions.
         */
        void draw2DRadar(Utils::Vector2D pos, Utils::Vector2D size, std::vector<Utils::Vector2D> baseShips) {
            if (!g_drawing)
                return;

            SDL_Rect rec = { (int)pos.x, (int)pos.y, (int)size.x, (int)size.y };
            g_drawing->fillRectangle({150, 0, 222, 255}, rec);

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
            g_drawing->fillRectangle({255, 255, 255, 255}, recPos);
        }
    };

    /**
     * The World class manages the world's data and rendering.
     */
    class World {
    private:
        /** The WorldModel instance. */
        WorldModel m_model;
        /** The WorldView instance. */
        WorldView m_view;

    public:
        /**
         * Constructs a World instance with a default WorldModel and WorldView.
         */
        World()
            : m_model()
            , m_view(Drawing::g_drawing, m_model)
        {}

        /**
         * Updates the world's elements based on the elapsed time.
         * \param deltaTime The time elapsed since the last update in seconds.
         */
        void update(float deltaTime) {
            m_model.updateBackground(deltaTime);
        }

        /**
         * Renders the background elements.
         */
        void renderBackground() {
            if (!m_view.drawBackground()) {
                m_model.initBackground();
            }
        }

        /**
         * Renders a 2D radar display on the screen.
         * \param pos The position of the radar display.
         * \param size The size of the radar display.
         * \param baseShips A vector of base ship positions.
         */
        void render2DRadar(Utils::Vector2D pos, Utils::Vector2D size, std::vector<Utils::Vector2D> baseShips) {
            m_view.draw2DRadar(pos, size, baseShips);
        }
    }; extern World* g_world;

} // Game

#endif //BOSCONIAN_WORLD_H
