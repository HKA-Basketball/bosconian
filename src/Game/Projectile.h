#ifndef BOSCONIAN_PROJECTILE_H
#define BOSCONIAN_PROJECTILE_H

#include <cmath>
#include <SDL.h>
#include "../../includes.h"
#include "../Drawing/Graphics.h"
#include "../Utilities/GlobalVars.h"

namespace Game {

    class ProjectileModel {
    public:
        ProjectileModel(float x, float y, float speed, float angle) :
                m_x(x - 4),
                m_y(y - 4),
                m_speed(speed),
                m_angle(angle),
                m_width(8),
                m_height(8) {
            m_active = true;
        }

        void update(float deltaTime) {
            // Calculate the new position of the projectile based on the angle.
            float angleInRadians = Utils::Math::normalizeAngle360(m_angle - 90.f) * M_PI / 180.0;

            // Calculate the direction components based on the angle.
            Utils::Vector2D direction = {static_cast<float>(cos(angleInRadians)), static_cast<float>(sin(angleInRadians))};
            direction.normalize();

            // Calculate the velocity components based on the speed.
            float velocityX = m_speed * direction.x;
            float velocityY = m_speed * direction.y;

            // Calculate the displacement in x and y directions.
            float dx = velocityX * deltaTime;
            float dy = velocityY * deltaTime;

            // Update the position of the projectile with subpixel positioning.
            m_x += dx;
            m_y += dy;

            if ((m_x < 0))
                m_x += Utils::GlobalVars::lvlWidth;

            if ((m_x > Utils::GlobalVars::lvlWidth))
                m_x -= Utils::GlobalVars::lvlWidth;

            if ((m_y < 0))
                m_y += Utils::GlobalVars::lvlHeight;

            if ((m_y > Utils::GlobalVars::lvlHeight))
                m_y -= Utils::GlobalVars::lvlHeight;
        }

        float getX() const {
            return m_x;
        }

        float getY() const {
            return m_y;
        }

        int getWidth() const {
            return m_width;
        }

        int getHeight() const {
            return m_height;
        }

        bool getActive() const {
            return m_active;
        }

        void setActive(bool val) {
            m_active = val;
        }

    private:
        float m_x;
        float m_y;
        float m_speed;
        int m_width;
        int m_height;
        float m_angle;
        bool m_active;
    };

    class ProjectileView {
    public:
        ProjectileView(Drawing::Graphics* graphics, const ProjectileModel& model) :
                m_drawing(graphics),
                m_model(model) {
        }

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

    private:
        Drawing::Graphics* m_drawing;
        const ProjectileModel& m_model;
    };

    class Projectile {
    public:
        Projectile(int x, int y, int speed, float angle) :
                m_model(x, y, speed, angle),
                m_view(Drawing::g_drawing, m_model) {
        }

        bool isOffscreen() const {
            Utils::Vector2D worldPos = Utils::Vector2D(m_model.getX(), m_model.getY());
            Utils::Vector2D screenPos;
            Utils::render::WorldToScreen(worldPos, screenPos);
            return (screenPos.x < -200 || screenPos.x > Utils::GlobalVars::windowWidth || screenPos.y < -200 || screenPos.y > Utils::GlobalVars::windowHeight);
        }

        bool ProjectileHitsEntity(SDL_Rect entityHitbox)
        {
            // Create a SDL_Rect for the projectile hitbox
            SDL_Rect projectileHitbox = getHitbox();

            // Check if the bounding boxes of the projectile and entity intersect
            return (projectileHitbox.x < entityHitbox.x + entityHitbox.w &&
                    projectileHitbox.x + projectileHitbox.w > entityHitbox.x &&
                    projectileHitbox.y < entityHitbox.y + entityHitbox.h &&
                    projectileHitbox.y + projectileHitbox.h > entityHitbox.y);
        }

        SDL_Rect getHitbox()
        {
            SDL_Rect projectileHitbox = {
                    static_cast<int>(m_model.getX()),
                    static_cast<int>(m_model.getY()),
                    static_cast<int>(m_model.getWidth()),
                    static_cast<int>(m_model.getHeight())
            };

            return projectileHitbox;
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
