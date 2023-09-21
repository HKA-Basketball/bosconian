#ifndef BOSCONIAN_PROJECTILE_H
#define BOSCONIAN_PROJECTILE_H

#include <cmath>
#include <SDL.h>

#include "ProjectileModel.h"
#include "ProjectileView.h"

#include "../../includes.h"
#include "../Utilities/GlobalVars.h"
#include "../Physics/Hitbox.h"

namespace Game {

    class Projectile {
    public:
        Projectile(int x, int y, int speed, float angle) :
                m_model(x, y, speed, angle), m_view(m_model) {}

        bool isOffscreen() const {
            Utils::Vector2D worldPos = Utils::Vector2D(m_model.getX(), m_model.getY());
            Utils::Vector2D screenPos;
            Utils::render::WorldToScreen(worldPos, screenPos);
            return (screenPos.x < -200 || screenPos.x > Utils::GlobalVars::windowWidth || screenPos.y < -200 || screenPos.y > Utils::GlobalVars::windowHeight);
        }

        bool ProjectileHitsEntity(SDL_Rect entityHitbox)
        {
            // Create a SDL_Rect for the projectile hitbox
            SDL_Rect projectileHitbox = (SDL_Rect) getHitbox();

            // Check if the bounding boxes of the projectile and entity intersect
            return (projectileHitbox.x < entityHitbox.x + entityHitbox.w &&
                    projectileHitbox.x + projectileHitbox.w > entityHitbox.x &&
                    projectileHitbox.y < entityHitbox.y + entityHitbox.h &&
                    projectileHitbox.y + projectileHitbox.h > entityHitbox.y);
        }

        Physics::Hitbox getHitbox() {
            return m_model.getHitbox();
        }

        void setActive(bool val) {
            m_model.setActive(val);
        }

        bool getActive() {
            return m_model.getActive();
        }

        void update(float deltaTime) {
            if (m_model.getActive()) {
                m_model.update(deltaTime);
            }
        }

        void render() const {
            if (m_model.getActive()) {
                m_view.render();
            }
        }

    private:
        ProjectileModel m_model;
        ProjectileView m_view;
    };

} // Game

#endif //BOSCONIAN_PROJECTILE_H
