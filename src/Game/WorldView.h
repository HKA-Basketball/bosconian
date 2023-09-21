#ifndef BOSCONIAN_WORLDVIEW_H
#define BOSCONIAN_WORLDVIEW_H

#include "WorldModel.h"
#include "../Utilities/GlobalVars.h"
#include "../Drawing/Graphics.h"
#include "../../includes.h"

namespace Game {

    /**
     * The WorldView class handles the rendering of the world's visual elements.
     */
    class WorldView {
    private:
        /** The drawing graphics interface. */
        Drawing::Graphics* g_drawing{Drawing::g_drawing};
        /** A reference to the WorldModel. */
        const Game::WorldModel& m_model;

    public:
        /**
         * Constructs a WorldView instance with the specified drawing graphics and WorldModel.
         * \param drawing The drawing graphics interface to use.
         * \param model A constant reference to the WorldModel instance.
         */
        explicit WorldView(const Game::WorldModel& model) : m_model(model) {}

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

}

#endif //BOSCONIAN_WORLDVIEW_H
