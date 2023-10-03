#ifndef BOSCONIAN_SPY_H
#define BOSCONIAN_SPY_H


#include "Entity.h"
#include "../../Utilities/Math.h"
#include "../../Utilities/Random.h"

class Spy : public Entity {
    Position* playerPositions;

    Vector2D startPosition;
    Vector2D targetPosition;
    bool returningToBase{false};
    bool loaded{false};

    const float attackThreshold{std::max(Config::screenWidth, Config::screenHeight) * 0.45f};
    const float closeEnoughDistance{100.f};
    const float minDistanceToUnload{120.f};

public:
    explicit Spy(const Vector2D &position, const Degree angle, Position* playerPositions)
            : Entity(position, angle), startPosition(position), playerPositions(playerPositions) {

        points = 123; /* TODO Random Value */
        speed = 155.0f;
        spriteInfo = SpriteInfo::SPY;
    }

    void update(float deltaTime) override {
        if(!loaded || defeated) {
            Entity::update(deltaTime);
            return;
        }

        Vector2D currentPosition = position.getCenterPosition();

        // Find the closest wrapped player position
        Vector2D closestPlayerPosition = playerPositions->getCenterPosition();
        float minDistanceToPlayer = (currentPosition - closestPlayerPosition).length();

        for (const Vector2D& wrappedPos : playerPositions->getWrappedPositions()) {
            float distance = (currentPosition - wrappedPos).length();
            if (distance < minDistanceToPlayer) {
                minDistanceToPlayer = distance;
                closestPlayerPosition = wrappedPos;
            }
        }

        float distanceToStart = (currentPosition - startPosition).length();

        if (returningToBase) {
            if (distanceToStart <= minDistanceToUnload) {
                loaded = false;
                returningToBase = false;
            } else {
                targetPosition = startPosition;
            }
        } else {
            if (minDistanceToPlayer <= attackThreshold) {
                if (minDistanceToPlayer <= closeEnoughDistance) {
                    returningToBase = true;
                } else {
                    targetPosition = closestPlayerPosition;
                }
            }
        }

        Vector2D direction = (targetPosition - currentPosition).normalized();
        float targetAngle = std::atan2(direction.y, direction.x) * 180.0f / static_cast<float>(M_PI);
        angle = Math::normalizeAngle180(targetAngle + 90.0f);

        Entity::update(deltaTime);
    }

    void searchForPlayer() {
        loaded = true;
    }

    bool returnedToBasePlayer() {
        return !loaded;
    }

    bool isLoaded() const {
        return loaded;
    }
};

#endif //BOSCONIAN_SPY_H
