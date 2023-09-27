#ifndef BOSCONIAN_PROJECTILE_H
#define BOSCONIAN_PROJECTILE_H

#include "Entity.h"

#include "../../Utilities/Vector2D.h"
#include "../../Utilities/Degree.h"

class Projectile : public Entity {
public:
    explicit Projectile(const Vector2D& position, const Degree angle) : Entity(position, angle) {
        speed = 1000.f;
        hitbox = {{0, 0}, {10, 10}};
    }

};

typedef std::vector<Projectile*> Projectiles;

#endif //BOSCONIAN_PROJECTILE_H
