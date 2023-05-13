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
                m_x(x - 5),
                m_y(y - 5),
                m_startX(x - 5),
                m_startY(y - 5),
                m_speed(speed),
                m_angle(angle),
                m_width(10),
                m_height(10) {
        }

        void update() {
            // Calculate the new position of the projectile based on the angle.
            float angleRadians = (90.0f - m_angle) * M_PI / 180.0f;
            float dx = m_speed * std::cos(angleRadians);
            float dy = -m_speed * std::sin(angleRadians);

            //TODO: Fix speed and angle at oblique angle
            /*if (std::abs(m_angle) == 45 || std::abs(m_angle) == 135) {
                dx /= std::sqrt(2.0f);
                dy /= std::sqrt(2.0f);
            }*/
            // Update the position of the projectile in world coordinates.
            m_x += dx;
            m_y += dy;

            if (m_x < 0) {
                m_x += Utils::GlobalVars::lvlWidth;
            }
            else if (m_x > Utils::GlobalVars::lvlWidth) {
                m_x -= Utils::GlobalVars::lvlWidth;
            }
            if (m_y < 0) {
                m_y += Utils::GlobalVars::lvlHeight;
            }
            else if (m_y > Utils::GlobalVars::lvlHeight) {
                m_y -= Utils::GlobalVars::lvlHeight;
            }
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

    private:
        int m_x;
        int m_y;
        int m_startX;
        int m_startY;
        int m_speed;
        int m_width;
        int m_height;
        float m_angle;
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

        void update() {
            m_model.update();
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

        void update() {
            m_controller.update();
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
