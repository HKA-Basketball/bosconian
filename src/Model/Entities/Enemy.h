#ifndef BOSCONIAN_ENEMY_H
#define BOSCONIAN_ENEMY_H

#include "Entity.h"
#include "../../Utilities/Math.h"
#include "../../Utilities/Random.h"

class Enemy : public Entity {
    Vector2D playerPosition{500, 500};
    Vector2D targetPosition;
    bool needNewPosition{true};

    const float attackThreshold{250.0f};
    const float detectionRange{150.f};

public:
    explicit Enemy(const Vector2D& position, const Degree angle) : Entity(position, angle) {
        speed = 155.0f;
        spriteInfo = Random::getRandomOne(
                SpriteInfo::E_TYPE,
                SpriteInfo::I_TYPE_NORM,
                SpriteInfo::P_TYPE_NORM
        );
    }

    void updatePlayerPosition(const Vector2D& newPlayerPosition) {
        playerPosition = newPlayerPosition;
    }

    void update(float deltaTime) override {
        float distance = (position.getCenterPosition() - playerPosition).length();

        if (distance <= attackThreshold) {
            targetPosition = playerPosition;
        } else if (distance <= detectionRange || needNewPosition) {
            setRandomTargetPos();
        }

        /* TODO 45 Degree steps so we can shoot him */
        Vector2D direction = (targetPosition - position.getCenterPosition()).normalized();
        float targetAngle = std::atan2(direction.y, direction.x) * 180.0f / M_PI;
        angle = Math::normalizeAngle180(targetAngle + 90.0f);

        Entity::update(deltaTime);
    }

private:
    void setRandomTargetPos() {
        if (needNewPosition) {
            // TODO: Level Size
            float randomX = 1200 * static_cast<float>(rand()) / RAND_MAX;
            float randomY = 1200 * static_cast<float>(rand()) / RAND_MAX;
            targetPosition = {randomX, randomY};
            needNewPosition = false;
        }
    }

};

#endif //BOSCONIAN_ENEMY_H
