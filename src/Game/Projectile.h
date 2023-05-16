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
        ProjectileModel(int x, int y, int speed, float angle) :
                m_x(x - 4),
                m_y(y - 4),
                m_speed(speed),
                m_angle(angle),
                m_width(8),
                m_height(8) {
            m_activ = true;
        }

        void update(float speed) {
            // Calculate the new position of the projectile based on the angle.
            float angleInRadians = Utils::GlobalVars::normalizeAngle360(m_angle - 90.f) * M_PI / 180.0;
            float dx = speed * cos(angleInRadians);
            float dy = speed * sin(angleInRadians);

            // Update the position of the projectile in world coordinates.
            m_x += static_cast<int>(std::round(dx));
            m_y += static_cast<int>(std::round(dy));

            if ((m_x < 0))
                m_x += Utils::GlobalVars::lvlWidth;

            if ((m_x > Utils::GlobalVars::lvlWidth))
                m_x -= Utils::GlobalVars::lvlWidth;

            if ((m_y < 0))
                m_y += Utils::GlobalVars::lvlHeight;

            if ((m_y > Utils::GlobalVars::lvlHeight))
                m_y -= Utils::GlobalVars::lvlHeight;
        }

        int getX() const {
            return m_x;
        }

        int getY() const {
            return m_y;
        }

        int getWidth() const {
            return m_width;
        }

        int getHeight() const {
            return m_height;
        }

        bool getActiv() const {
            return m_activ;
        }

        void setActiv(bool val) {
            m_activ = val;
        }

    private:
        int m_x;
        int m_y;
        int m_speed;
        int m_width;
        int m_height;
        float m_angle;
        bool m_activ;
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

            Utils::GlobalVars::WorldToScreen(worldPos, screenPos);

            SDL_Rect rect = { (int)screenPos.x, (int)screenPos.y, m_model.getWidth(), m_model.getHeight() };
            m_drawing->fillRectangleOutline({ 255, 255, 255, 255 }, rect);
        }

        Drawing::Graphics* getRenderer() const {
            return m_drawing;
        }

    private:
        Drawing::Graphics* m_drawing;
        const ProjectileModel& m_model;
    };

    class ProjectileController {
    public:
        ProjectileController(ProjectileModel& model) :
                m_model(model) {
        }

        void update(float speed) {
            m_model.update(speed);
        }

    private:
        ProjectileModel& m_model;
    };

    class Projectile {
    public:
        Projectile(Drawing::Graphics* graphics, int x, int y, int speed, float angle) :
                m_model(x, y, speed, angle),
                m_view(graphics, m_model),
                m_controller(m_model) {
        }

        bool isOffscreen() const {
            int m_x = m_model.getX();
            int m_y = m_model.getY();

            Utils::Vector2D worldPos = Utils::Vector2D(m_x, m_y);
            Utils::Vector2D screenPos;
            Utils::GlobalVars::WorldToScreen(worldPos, screenPos);
            return (screenPos.x < -50 || screenPos.x > Utils::GlobalVars::gameWindowWidth || screenPos.y < -50 || screenPos.y > Utils::GlobalVars::gameWindowHeight);
        }

        bool ProjectileHitsEntity(SDL_Rect entityHitbox)
        {
            // Create a SDL_Rect for the projectile hitbox
            SDL_Rect projectileHitbox = {
                    static_cast<int>(m_model.getX()),
                    static_cast<int>(m_model.getY()),
                    static_cast<int>(m_model.getWidth()),
                    static_cast<int>(m_model.getHeight())
            };

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

        void setActiv(bool val) {
            m_model.setActiv(val);
        }

        bool getActiv() {
            return m_model.getActiv();
        }

        void update(float speed) {
            m_controller.update(speed);
        }

        void render() const {
            m_view.render();
        }

    private:
        ProjectileModel m_model;
        ProjectileView m_view;
        ProjectileController m_controller;
    };

} // Game

#endif //BOSCONIAN_PROJECTILE_H
