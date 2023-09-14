#ifndef BOSCONIAN_MOVINGBEHAVIOUR_H
#define BOSCONIAN_MOVINGBEHAVIOUR_H

#include "Behaviour.h"
#include "../EntityView.h"
#include "../EntityModel.h"

namespace Game {

    class MovingBehavior : public Behavior {
    public:
        void update(EntityModel &model, float deltaTime = 0.f) override {
            Utils::Vector2D currentPosition = model.getOrigin();
            Utils::Vector2D playerPosition = Utils::GlobalVars::cameraPos;
            float distance = (currentPosition - playerPosition).length();
            // TODO: may add viewAngle?
            float attackThreshold = 250.0f;

            if (distance <= attackThreshold) {
                move2Pos(model, playerPosition, deltaTime);
            } else {
                if (needNewPos) {
                    float randomX = Utils::GlobalVars::lvlWidth * static_cast<float>(rand()) / RAND_MAX;
                    float randomY = Utils::GlobalVars::lvlHeight * static_cast<float>(rand()) / RAND_MAX;
                    targetPos = {randomX, randomY};
                    needNewPos = false;
                }

                move2Pos(model, targetPos, deltaTime);
            }

            if (model.isTriggerAnimation() && !animationStart) {
                animationStart = true;
                animationTime = 0.f;
                Sound::g_sound->playSound(Sound::SOUND_EXPLODE, 2, 0);
            }

            if (animationEnd)
                model.setActive(false);
        }

        void update(EntityView &view, float deltaTime = 0.f) override {
            if (!animationStart)
                return;

            animationTime += deltaTime * 1000.f;

            float progress = animationTime / animationDuration;
            progress = std::clamp(progress, 0.f, 1.f);
            int imageIndex = static_cast<int>(progress * (explosionImages.size() - 1));

            view.setTexture(explosionImages[imageIndex]);

            if (animationTime >= animationDuration)
                animationEnd = true;
        }

    private:
        Utils::Vector2D targetPos;
        bool needNewPos = true;

        bool animationStart = false;
        bool animationEnd = false;
        float animationTime = 0.f;
        const float animationDuration = 250.f;
        std::vector<std::string> explosionImages = {
                "astro-explo-01",
                "astro-explo-02",
                "astro-explo-03"
        };


        int roundToNearestMultiple(int angleInDegrees, int multiple) {
            int remainder = angleInDegrees % multiple;
            int result = angleInDegrees - remainder;
            if (remainder >= multiple / 2) {
                result += multiple;
            }
            return result;
        }

        void move2Pos(EntityModel &model, Utils::Vector2D pos2move, float deltaTime = 0.f) {

            Utils::Vector2D direction = pos2move - model.getOrigin();

            // Check if the player is spotted
            float detectionRange = 150.f; // Adjust the range as needed
            float distance = direction.length();

            if (distance <= detectionRange) {
                needNewPos = true;
            }

            direction.normalize();

            float speed = 190 * deltaTime;
            Utils::Vector2D newPosition;

            // Calculate the closest 45-degree angle
            float angle = std::atan2(direction.y, direction.x);
            int angleInDegrees = static_cast<int>(round(angle * 180 / M_PI));
            int closestAngleInDegrees = roundToNearestMultiple(angleInDegrees, 45);
            float closestAngle = closestAngleInDegrees * M_PI / 180;

            // Calculate the target direction based on the closest angle
            Utils::Vector2D targetDirection(std::cos(closestAngle), std::sin(closestAngle));

            // Calculate the dot product between the current direction and the target direction
            float dotProduct = direction.dot(targetDirection);

            // Calculate the turning angle based on the dot product and the turning speed
            float turningAngle = std::acos(dotProduct) * speed;

            // Rotate the direction towards the target direction by the turning angle
            Utils::Vector2D newDirection = direction.rotate(turningAngle);

            // Calculate the new position using the new direction and speed
            newPosition = model.getOrigin() + newDirection * speed;

            float angleF = std::atan2(newDirection.y, newDirection.x);
            float angleInDegreesF = angleF * 180 / M_PI;
            float targetAngle = Utils::Math::normalizeAngle180(angleInDegreesF + 90.f);

            // Apply a smoothing factor
            const float smoothingFactor = 0.1f;

            float currentAngle = model.getAngle();
            float smoothedAngle =
                    currentAngle + smoothingFactor * Utils::Math::normalizeAngle180(targetAngle - currentAngle);

            model.setAngle(smoothedAngle);

            Utils::Math::wrapPos(&newPosition);

            model.setOrigin(newPosition);
        }
    };
}

#endif //BOSCONIAN_MOVINGBEHAVIOUR_H
