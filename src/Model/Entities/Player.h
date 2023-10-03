#ifndef BOSCONIAN_PLAYER_H
#define BOSCONIAN_PLAYER_H

#include <cmath>
#include <vector>

#include "Entity.h"
#include "Projectile.h"

#include "../../Physics/Hitbox.h"

#include "../../Utilities/Vector2D.h"
#include "../../Utilities/Degree.h"
#include "../World.h"


class Player : public Entity {
private:
    float elapsedTimeSinceLastShot{0.f};
    float shotCooldownDuration{0.25f};
    Projectiles* projectiles = new Projectiles(0);

public:
    explicit Player(const Vector2D& position, const Degree angle) : Entity(position, angle) {
        speed = 200.0f;
        spriteInfo = SpriteInfo::PLAYER;
    }

    void update(float deltaTime) override {
        Entity::update(deltaTime);

        elapsedTimeSinceLastShot += deltaTime;

        for (Projectile* projectile : *projectiles) {
            projectile->update(deltaTime);
        }
    }

    // Function to make the player shoot.
    bool shoot(float deltaTime) {
        if (elapsedTimeSinceLastShot >= shotCooldownDuration) {
            projectiles->push_back(new Projectile(position.getCenterPosition(), angle));
            projectiles->push_back(new Projectile(position.getCenterPosition(), angle + 180));
            elapsedTimeSinceLastShot = 0; // Reset the timer
            return true;
        }

        return false;
    }

    void reset() {
        defeated = false;
        dead = false;

        speed = 200.0f;
        spriteInfo = SpriteInfo::PLAYER;
    }

    Projectiles* getProjectiles() const { return projectiles; }
};

#endif //BOSCONIAN_PLAYER_H
