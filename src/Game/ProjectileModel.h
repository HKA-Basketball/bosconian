#ifndef BOSCONIAN_PROJECTILEMODEL_H
#define BOSCONIAN_PROJECTILEMODEL_H

#include "../Physics/Hitbox.h"
#include "../Utilities/GlobalVars.h"
#include "../Drawing/Graphics.h"
#include "../../includes.h"
#include <SDL.h>
#include <cmath>

namespace Game {

    class ProjectileModel {
    public:
        ProjectileModel(float x, float y, float speed, float angle) :
                m_x(x - 4),
                m_y(y - 4),
                m_speed(speed),
                m_angle(angle),
                m_width(8),
                m_height(8),
                m_active(true),
                m_hitbox(Physics::Hitbox(Utils::Vector2D(m_x, m_y),
                                         Utils::Vector2D(m_width, m_height)
                )) {}

        void update(float deltaTime) {
            // Calculate the new position of the projectile based on the angle.
            float angleInRadians = Utils::Math::normalizeAngle360(m_angle - 90.f) * M_PI / 180.0;

            // Calculate the direction components based on the angle.
            Utils::Vector2D direction = {static_cast<float>(cos(angleInRadians)),
                                         static_cast<float>(sin(angleInRadians))};
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

            m_hitbox.updatePosition(Utils::Vector2D(m_x, m_y));
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

        Physics::Hitbox getHitbox() const {
            return m_hitbox;
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

        Physics::Hitbox m_hitbox;
    };
}

#endif //BOSCONIAN_PROJECTILEMODEL_H
