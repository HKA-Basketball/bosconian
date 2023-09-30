#ifndef BOSCONIAN_SHIP_H
#define BOSCONIAN_SHIP_H

#include "Entity.h"
#include "../../Utilities/Math.h"
#include "../../Utilities/Random.h"

class Ship : public Entity {
    WrappedPositions playerPositions;

    Vector2D targetPosition;
    bool needNewPosition{true};

    const float attackThreshold{std::max(Config::screenWidth, Config::screenHeight) * 0.45f};


public:
    explicit Ship(const Vector2D &position, const Degree angle) : Entity(position, angle) {
        speed = 155.0f;
        spriteInfo = Random::getRandomOne(
                SpriteInfo::E_TYPE,
                SpriteInfo::I_TYPE_NORM,
                SpriteInfo::P_TYPE_NORM
        );
    }

    void updatePlayerPosition(const WrappedPositions& newPlayerPositions) {
        playerPositions = newPlayerPositions;
    }

    /* TODO 45 Degree steps so we can shoot him */
    void update(float deltaTime) override {

        // Find the closest wrapped player position
        Vector2D closestPosition = playerPositions.at(Position::CENTER);
        float minDistance = (position.getCenterPosition() - closestPosition).length();

        for (const Vector2D& wrappedPos : playerPositions) {
            float distance = (position.getCenterPosition() - wrappedPos).length();
            if (distance < minDistance) {
                minDistance = distance;
                closestPosition = wrappedPos;
            }
        }

        // Check if the enemy has reached the target position
        if ((position.getCenterPosition() - targetPosition).length() < speed * deltaTime) {
            needNewPosition = true;
        }

        // Follow the player if within attackThreshold, otherwise move to a random position
        if (minDistance <= attackThreshold) {
            targetPosition = closestPosition;
            needNewPosition = false; // The enemy has a new target, so it doesn't need a new position
        }

        if (needNewPosition) {
            setRandomTargetPos();
        }

        Vector2D direction = (targetPosition - position.getCenterPosition()).normalized();
        float targetAngle = std::atan2(direction.y, direction.x) * 180.0f / static_cast<float>(M_PI);
        angle = Math::normalizeAngle180(targetAngle + 90.0f);

        Entity::update(deltaTime);
    }

private:
    void setRandomTargetPos() {
        float randomX = Math::randomFloat(0, Config::screenWidth);
        float randomY = Math::randomFloat(0, Config::screenHeight);
        targetPosition = {randomX, randomY};
        needNewPosition = false;
    }

};

#endif //BOSCONIAN_SHIP_H
