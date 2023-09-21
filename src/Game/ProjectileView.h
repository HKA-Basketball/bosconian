#ifndef BOSCONIAN_PROJECTILEVIEW_H
#define BOSCONIAN_PROJECTILEVIEW_H

#include "ProjectileModel.h"
#include "../Physics/Hitbox.h"
#include "../Utilities/GlobalVars.h"
#include "../Drawing/Graphics.h"
#include "../../includes.h"
#include <SDL.h>
#include <cmath>

class ProjectileView {
private:
    /** The drawing graphics interface. */
    Drawing::Graphics* m_drawing{Drawing::g_drawing};
    const Game::ProjectileModel& m_model;

public:
    explicit ProjectileView(const Game::ProjectileModel& model) : m_model(model) {}

    void render() const {
        // Render the projectile.

        Utils::Vector2D worldPos = Utils::Vector2D(m_model.getX(), m_model.getY());
        Utils::Vector2D screenPos;

        Utils::render::WorldToScreen(worldPos, screenPos);

        SDL_FRect rect = { screenPos.x, screenPos.y, (float)m_model.getWidth(), (float)m_model.getHeight() };
        m_drawing->fillRectangleOutline({ 255, 255, 255, 255 }, rect);
    }

    Drawing::Graphics* getRenderer() const {
        return m_drawing;
    }
};

#endif //BOSCONIAN_PROJECTILEVIEW_H
