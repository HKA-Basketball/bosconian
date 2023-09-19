#ifndef BOSCONIAN_SPY_H
#define BOSCONIAN_SPY_H

#include "Entity.h"
#include "../../Drawing/Texture.h"

namespace Game {

    class Spy : public Entity {
    private:
        bool isPlayerSpotted;
        bool isMovingTowardsPlayer;
        Utils::Vector2D startPos;
        bool once = false;

    public:
        Spy(Utils::Vector2D pos, float deg, std::shared_ptr<Drawing::Texture> img, EntityType type, Uint64 pts)
        : Entity(pos, deg, img, type, pts) {}

        Spy(Utils::Vector2D pos, float deg, std::shared_ptr<Drawing::Texture> img, Utils::Vector2D hitboxPos,
                Utils::Vector2D hitboxSize, EntityType type, Uint64 pts)
        : Entity(pos, deg, img, hitboxPos, hitboxSize, type, pts) {}

        void updateBehaviour(float deltaTime = 0.f) override {
            if (!once) {
                startPos = this->getOrigin();
                once = true;
            }

            // Check if the spy has spotted the player
            if (isPlayerSpotted) {
                // Move away from the player
                moveAwayFromPlayer(deltaTime);
            } else {
                // Search for the player
                searchForPlayer(deltaTime);
            }
        }

    private:
        int roundToNearestMultiple(int angleInDegrees, int multiple) {
            int remainder = angleInDegrees % multiple;
            int result = angleInDegrees - remainder;
            if (remainder >= multiple / 2) {
                result += multiple;
            }
            return result;
        }

        inline void searchForPlayer(float deltaTime = 0.f) {
            // Perform search behavior to find the player

            Utils::Vector2D direction = Utils::GlobalVars::cameraPos - this->getOrigin();

            // Check if the player is spotted
            float detectionRange = 150.f; // Adjust the range as needed
            float distance = direction.length();

            if (distance <= detectionRange) {
                isPlayerSpotted = true;
                isMovingTowardsPlayer = false;
            }

            direction.normalize();

            float speed = 250 * deltaTime;
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
            newPosition = this->getOrigin() + newDirection * speed;

            float angleF = std::atan2(newDirection.y, newDirection.x);
            float angleInDegreesF = angleF * 180 / M_PI;
            float targetAngle = Utils::Math::normalizeAngle180(angleInDegreesF + 90.f);

            // Apply a smoothing factor
            const float smoothingFactor = 0.1f;

            float currentAngle = this->getAngle();
            float smoothedAngle =
                    currentAngle + smoothingFactor * Utils::Math::normalizeAngle180(targetAngle - currentAngle);

            this->setAngle(smoothedAngle);

            Utils::Math::wrapPos(&newPosition);

            this->setOrigin(newPosition);
        }

        inline void moveAwayFromPlayer(float deltaTime = 0.f) {
            if (!this->isTriggerAnimation())
                Utils::GlobalVars::condition = 1;

            // Calculate the direction away from the player
            Utils::Vector2D direction2Player = this->getOrigin() - Utils::GlobalVars::cameraPos;
            Utils::Vector2D direction = startPos - this->getOrigin();

            float distance2StartPos = direction.length();

            float detectionRange = 600.f; // Adjust the range as needed
            float distance = direction2Player.length();

            if (distance >= detectionRange) {
                isPlayerSpotted = false;
                isMovingTowardsPlayer = true;
            }

            direction.normalize();

            float speed = 250 * deltaTime;
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
            newPosition = this->getOrigin() + newDirection * speed;

            float angleF = std::atan2(newDirection.y, newDirection.x);
            float angleInDegreesF = angleF * 180 / M_PI;
            float targetAngle = Utils::Math::normalizeAngle180(angleInDegreesF + 90.f);

            // Apply a smoothing factor
            const float smoothingFactor = 0.1f;

            float currentAngle = this->getAngle();
            float smoothedAngle =
                    currentAngle + smoothingFactor * Utils::Math::normalizeAngle180(targetAngle - currentAngle);

            this->setAngle(smoothedAngle);

            Utils::Math::wrapPos(&newPosition);

            this->setOrigin(newPosition);

            if (distance2StartPos <= 50.f) {
                // TODO: Start Attack
                Utils::GlobalVars::condition = 2;
                this->setActive(false);
            }
        }
    };
}

#endif //BOSCONIAN_SPY_H