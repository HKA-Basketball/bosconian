#ifndef BOSCONIAN_CANON_H
#define BOSCONIAN_CANON_H

#include "Entity.h"

namespace Game {

    class Canon : public Entity {
    private:
        bool canShoot = false;
        Uint64 timeSinceLastProjectile = 0;
        const Uint64 projectileInterval = 1500;
        std::string texture;
        float viewDirection;
        float viewAngle = 45.f;
        float viewLength = 400.0f;

        Utils::Vector2D canonPosition;

    public:
        void updateBehaviour(float deltaTime) override {
            Utils::Vector2D playerPosition = Utils::GlobalVars::cameraPos;
            canonPosition = this->getOrigin();

            Utils::Vector2D direction = playerPosition - canonPosition;
            float distance = direction.length();
            direction.normalize();

            // Calculate the angle between the Canon and the player
            float angleToPlayer = std::atan2(direction.y, direction.x);
            angleToPlayer = angleToPlayer * (180.0f / M_PI); // Convert radians to degrees
            float targetAngle = Utils::Math::normalizeAngle180(angleToPlayer + 90.f);

            float startAngle = viewDirection - (viewAngle / 2.0f);
            float endAngle = viewDirection + (viewAngle / 2.0f);
            angleToPlayer = Utils::Math::normalizeAngle360(angleToPlayer);
            startAngle = Utils::Math::normalizeAngle360(startAngle);
            endAngle = Utils::Math::normalizeAngle360(endAngle);

            // Check if the player is within the view area
            bool playerInViewArea = false;
            if (startAngle <= endAngle) {
                playerInViewArea = (angleToPlayer >= startAngle && angleToPlayer <= endAngle);
            } else {
                playerInViewArea = (angleToPlayer >= startAngle || angleToPlayer <= endAngle);
            }

            bool playerWithinDistance = distance <= viewLength;

            if (playerInViewArea && playerWithinDistance && this->isActive()) {
                Uint64 currentTime = SDL_GetTicks64();
                if (currentTime - timeSinceLastProjectile >= projectileInterval) {
                    canShoot = true;
                    Sound::g_sound->playSound(Sound::SOUND_SHOOT, 4, 0);

                    Game::Projectile *newProjectile = new Game::Projectile(this->getOrigin().x, this->getOrigin().y,
                                                                           180, targetAngle);

                    this->addProjectile(newProjectile);
                    timeSinceLastProjectile = currentTime;
                }
            }
        }
    };
}
#endif //BOSCONIAN_CANON_H
