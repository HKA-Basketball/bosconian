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
    static constexpr float DEFAULT_VIEW_ANGLE = 100.f;
    static constexpr float DEFAULT_VIEW_LENGTH = 400.0f;
    static constexpr float SHOT_COOLDOWN_DURATION = 1.5f;

    Position* playerPositions;
    float elapsedTimeSinceLastShot{0.f};
    float viewAngle{DEFAULT_VIEW_ANGLE};
    float viewLength{DEFAULT_VIEW_LENGTH};

    Projectiles* projectiles = new Projectiles(0);
public:
    explicit Cannon(const Vector2D& position, const Degree angle, Position* playerPositions, SpriteInfo spriteInfo, SpriteInfo explosionSpriteInfo) : Entity(position, angle), playerPositions(playerPositions) {
        this->spriteInfo = spriteInfo;
        points = 200;
        hitbox = {position, {75, 75}};
        explosion = {{explosionSpriteInfo}};
    }

    void update(float deltaTime) override {
        Entity::update(deltaTime);
        hitbox.updateAngle(0);

        elapsedTimeSinceLastShot += deltaTime;

        Vector2D direction = playerPositions->getCenterPosition() - position.getCenterPosition();
        float distance = direction.length();
        direction.normalize();

        float angleToPlayer = std::atan2(direction.y, direction.x) * (180.0f / M_PI);
        float targetAngle = Math::normalizeAngle180(angleToPlayer + 90.f);

        float startAngle = Math::normalizeAngle360(angle.getDegree() - (viewAngle / 2.0f));
        float endAngle = Math::normalizeAngle360(angle.getDegree() + (viewAngle / 2.0f));
        angleToPlayer = Math::normalizeAngle360(angleToPlayer);

        bool playerInViewArea = (startAngle <= endAngle) ? (angleToPlayer >= startAngle && angleToPlayer <= endAngle) : (angleToPlayer >= startAngle || angleToPlayer <= endAngle);
        bool playerWithinDistance = distance <= viewLength;

        if (playerInViewArea && playerWithinDistance && elapsedTimeSinceLastShot >= SHOT_COOLDOWN_DURATION && !defeated) {
            elapsedTimeSinceLastShot = 0;
            auto newProjectile = new Projectile(position.getCenterPosition(), targetAngle);
            newProjectile->setSpeed(350.f);
            projectiles->push_back(newProjectile);
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

    Projectiles *getProjectiles() const {
        return projectiles;
    }

    Position* getPlayerPositions() const {
        return playerPositions;
    }
};

#endif //BOSCONIAN_CANNON_H
