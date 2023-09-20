#ifndef BOSCONIAN_ENEMY_H
#define BOSCONIAN_ENEMY_H

#include "Entity.h"

namespace Game {

    class Enemy : public Entity {
    private:
        std::vector<std::string> images{"E-Type", "I-Type-norm", "P-Type-norm"};
        std::vector<int> pts{70, 50, 60};

        const float attackThreshold = 250.0f;
        const float detectionRange = 150.f;

        Utils::Vector2D targetPos;
        bool needNewPos = true;

    public:
        Enemy(const Utils::Vector2D& pos, float deg, const std::shared_ptr<Drawing::Texture>& img, EntityType type, Uint64 pts)
        : Entity(pos, deg, img, type, pts) {
            initTexture();
        }

        Enemy(const Utils::Vector2D& pos, float deg, const std::shared_ptr<Drawing::Texture>& img, const Utils::Vector2D& hitboxPos,
                const Utils::Vector2D& hitboxSize, EntityType type, Uint64 pts)
        : Entity(pos, deg, img, hitboxPos, hitboxSize, type, pts) {}

        void initTexture() {
            int ranImg = rand() % images.size();
            std::shared_ptr<Drawing::Texture> img = std::make_shared<Drawing::Texture>(images[ranImg], getAngle(), true, "spritesheet.png");

        }

        void updateBehaviour(float deltaTime = 0.f) override {
            Utils::Vector2D currentPosition = this->getOrigin();
            Utils::Vector2D playerPosition = Utils::GlobalVars::cameraPos;
            float distance = (currentPosition - playerPosition).length();

            // Moving the attackThreshold as a class member constant
            if (distance <= attackThreshold) {
                move2Pos(playerPosition, deltaTime);
            } else {
                setRandomTargetPos();
                move2Pos(targetPos, deltaTime);
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

        void setRandomTargetPos() {
            if (needNewPos) {
                float randomX = Utils::GlobalVars::lvlWidth * static_cast<float>(rand()) / RAND_MAX;
                float randomY = Utils::GlobalVars::lvlHeight * static_cast<float>(rand()) / RAND_MAX;
                targetPos = {randomX, randomY};
                needNewPos = false;
            }
        }

        void move2Pos(const Utils::Vector2D& pos2move, float deltaTime = 0.f) {

            Utils::Vector2D direction = pos2move - this->getOrigin();

            // Check if the player is spotted
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

    };

}

#endif //BOSCONIAN_ENEMY_H
