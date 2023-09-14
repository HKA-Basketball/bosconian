#ifndef BOSCONIAN_CANONBEHAVIOUR_H
#define BOSCONIAN_CANONBEHAVIOUR_H

#include "Behaviour.h"
#include "../EntityView.h"
#include "../EntityModel.h"

namespace Game {

    class CanonBehavior : public Behavior {
    private:
        bool animationStart = false;
        bool animationEnd = false;
        bool canShoot = false;
        Uint64 timeSinceLastProjectile = 0;
        const Uint64 projectileInterval = 1500;
        std::string texture;
        float viewDirection;
        float viewAngle = 45.f;
        float viewLength = 400.0f;

        Utils::Vector2D canonPosition;

    public:
        CanonBehavior(std::string afterShoot, float initialViewDirection)
                : texture(afterShoot), viewDirection(initialViewDirection) {}

        void update(EntityModel &model, float deltaTime = 0.f) override {
            if (model.isTriggerAnimation() && !animationStart) {
                animationStart = true;
            }

            Utils::Vector2D playerPosition = Utils::GlobalVars::cameraPos;
            canonPosition = model.getOrigin();

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

            if (playerInViewArea && playerWithinDistance && model.isActive()) {
                Uint64 currentTime = SDL_GetTicks64();
                if (currentTime - timeSinceLastProjectile >= projectileInterval) {
                    canShoot = true;
                    Sound::g_sound->playSound(Sound::SOUND_SHOOT, 4, 0);

                    Game::Projectile *newProjectile = new Game::Projectile(model.getOrigin().x, model.getOrigin().y,
                                                                           180, targetAngle);

                    model.addProjectile(newProjectile);
                    timeSinceLastProjectile = currentTime;
                }
            }

            if (animationEnd)
                model.setActive(false);
        }

        void update(EntityView &view, float deltaTime = 0.f) override {
            drawView();

            if (!animationStart)
                return;

            view.setTexture(texture);

            animationEnd = true;
        }

    private:
        void drawView() {
            if (!Utils::GlobalVars::debugMode)
                return;

            Utils::Vector2D tmp1;
            Utils::Vector2D tmp2;

            // Calculate the start and end angles of the view cone
            float startAngle = viewDirection - (viewAngle / 2.0f);
            float endAngle = viewDirection + (viewAngle / 2.0f);

            float endX = canonPosition.x + viewLength * cos(startAngle * (M_PI / 180.0f));
            float endY = canonPosition.y + viewLength * sin(startAngle * (M_PI / 180.0f));

            Utils::render::WorldToScreen(canonPosition, tmp1);
            Utils::render::WorldToScreen({endX, endY}, tmp2);

            Drawing::g_drawing->line({255, 255, 255, 255}, tmp1, tmp2);

            endX = canonPosition.x + viewLength * cos(endAngle * (M_PI / 180.0f));
            endY = canonPosition.y + viewLength * sin(endAngle * (M_PI / 180.0f));
            Utils::render::WorldToScreen(canonPosition, tmp1);
            Utils::render::WorldToScreen({endX, endY}, tmp2);

            Drawing::g_drawing->line({255, 255, 255, 255}, tmp1, tmp2);

            Utils::Vector2D playerPosition = Utils::GlobalVars::cameraPos;

            // Calculate the angle between the Canon and the player
            float angleToPlayer = std::atan2(playerPosition.y - canonPosition.y, playerPosition.x - canonPosition.x);
            angleToPlayer = angleToPlayer * (180.0f / M_PI); // Convert radians to degrees
            angleToPlayer = Utils::Math::normalizeAngle360(angleToPlayer);
            startAngle = Utils::Math::normalizeAngle360(startAngle);
            endAngle = Utils::Math::normalizeAngle360(endAngle);

            // Check if the player's angle is within the view cone
            bool playerInCone = false;
            if (startAngle <= endAngle) {
                playerInCone = (angleToPlayer >= startAngle && angleToPlayer <= endAngle);
            } else {
                playerInCone = (angleToPlayer >= startAngle || angleToPlayer <= endAngle);
            }

            if (playerInCone) {
                endX = canonPosition.x + viewLength * cos(angleToPlayer * (M_PI / 180.0f));
                endY = canonPosition.y + viewLength * sin(angleToPlayer * (M_PI / 180.0f));
                Utils::render::WorldToScreen(canonPosition, tmp1);
                Utils::render::WorldToScreen({endX, endY}, tmp2);

                Drawing::g_drawing->line({255, 0, 0, 255}, tmp1, tmp2);
            }
        }
    };

}

#endif //BOSCONIAN_CANONBEHAVIOUR_H
