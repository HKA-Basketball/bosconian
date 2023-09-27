#ifndef BOSCONIAN_CANNON_H
#define BOSCONIAN_CANNON_H

#include <vector>
#include <cmath>

#include "Entity.h"
#include "Projectile.h"
#include "../../Utilities/Vector2D.h"
#include "../../Utilities/Math.h"

class Cannon : public Entity {
private:
    static constexpr float DEFAULT_VIEW_ANGLE = 90.f;
    static constexpr float DEFAULT_VIEW_LENGTH = 400.0f;
    static constexpr float SHOT_COOLDOWN_DURATION = 1.5f;

    Vector2D playerPosition{500, 500};
    float elapsedTimeSinceLastShot{0.f};
    float viewAngle{DEFAULT_VIEW_ANGLE};
    float viewLength{DEFAULT_VIEW_LENGTH};
    float viewDirection; // Initialize this as needed

    Projectiles* projectiles = new Projectiles(0);
public:
    explicit Cannon(const Vector2D& position, const Degree angle, SpriteInfo spriteInfo) : Entity(position, angle) {
        this->spriteInfo = spriteInfo;
    }

    Vector2D getPlayerPosition() const {
        return playerPosition;
    }

    void updatePlayerPosition(const Vector2D& newPlayerPosition) {
        playerPosition = newPlayerPosition;
    }

    void update(float deltaTime) override {
        Entity::update(deltaTime);

        elapsedTimeSinceLastShot += deltaTime;

        Vector2D direction = playerPosition - position;
        float distance = direction.length();
        direction.normalize();

        float angleToPlayer = std::atan2(direction.y, direction.x) * (180.0f / M_PI);
        float targetAngle = Math::normalizeAngle180(angleToPlayer + 90.f);

        float startAngle = Math::normalizeAngle360(viewDirection - (viewAngle / 2.0f));
        float endAngle = Math::normalizeAngle360(viewDirection + (viewAngle / 2.0f));
        angleToPlayer = Math::normalizeAngle360(angleToPlayer);

        bool playerInViewArea = (startAngle <= endAngle) ? (angleToPlayer >= startAngle && angleToPlayer <= endAngle) : (angleToPlayer >= startAngle || angleToPlayer <= endAngle);
        bool playerWithinDistance = distance <= viewLength;

        if (playerInViewArea && playerWithinDistance && elapsedTimeSinceLastShot >= SHOT_COOLDOWN_DURATION) {
            elapsedTimeSinceLastShot = 0;
            projectiles->push_back(new Projectile(position, targetAngle));
        }

        for (auto& projectile : *projectiles) {
            projectile->update(deltaTime);
        }
    }

    float getViewAngle() const {
        return viewAngle;
    }

    float getViewLength() const {
        return viewLength;
    }

    float getViewDirection() const {
        return viewDirection;
    }

    Projectiles *getProjectiles() const {
        return projectiles;
    }
};

#endif //BOSCONIAN_CANNON_H
