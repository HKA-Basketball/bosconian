#ifndef BOSCONIAN_SHIP_H
#define BOSCONIAN_SHIP_H

#include "Entity.h"
#include "../../Utilities/Vector2D.h"
#include "../../Utilities/Math.h"
#include "../../Utilities/Random.h"

class Ship : public Entity {
    Position* playerPositions;

    Vector2D targetPosition;
    bool needNewPosition{true};

    const float attackThreshold{std::max(Config::screenWidth, Config::screenHeight) * 0.45f};


public:
    explicit Ship(const Vector2D &position, const Degree angle, Position* playerPositions) : Entity(position, angle), playerPositions(playerPositions) {
        speed = 155.0f;
        spriteInfo = Random::getRandomOne(
            SpriteInfo::I_TYPE_NORM,
            SpriteInfo::P_TYPE_NORM,
            SpriteInfo::E_TYPE
        );

        hitbox = {position, {
            static_cast<float>(spriteMap.at(spriteInfo).w),
            static_cast<float>(spriteMap.at(spriteInfo).h)}
        };

        switch (spriteInfo) {
            default:
                points = 50;
                break;
            case SpriteInfo::P_TYPE_NORM:
                points = 60;
                break;
            case SpriteInfo::E_TYPE:
                points = 70;
                break;
        }
    }

    /* TODO 45 Degree steps so we can shoot him */
    void update(float deltaTime) override {

        // Find the closest wrapped player position
        Vector2D closestPosition = playerPositions->getCenterPosition();
        float minDistance = (position.getCenterPosition() - closestPosition).length();

        for (const Vector2D& wrappedPos : playerPositions->getWrappedPositions()) {
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
            float randomX = Random::randomFloat(0, Config::levelWidth);
            float randomY = Random::randomFloat(0, Config::levelHeight);
            targetPosition = {randomX, randomY};
            needNewPosition = false;
        }

        Vector2D direction = (targetPosition - position.getCenterPosition()).normalized();
        float targetAngle = std::atan2(direction.y, direction.x) * 180.0f / static_cast<float>(M_PI);
        angle = Math::normalizeAngle180(targetAngle + 90.0f);

        Entity::update(deltaTime);
    }

};

#endif //BOSCONIAN_SHIP_H
