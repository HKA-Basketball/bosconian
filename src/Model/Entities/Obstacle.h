#ifndef BOSCONIAN_OBSTACLE_H
#define BOSCONIAN_OBSTACLE_H

#include "Entity.h"

#include "../../Utilities/Vector2D.h"
#include "../../Utilities/Degree.h"
#include "../../Utilities/Random.h"

class Obstacle : public Entity {
public:
    explicit Obstacle(const Vector2D& position, const Degree angle) : Entity(position, angle) {
        spriteInfo = Random::getRandomOne(
                SpriteInfo::BOMB,
                SpriteInfo::ASTROID_01,
                SpriteInfo::ASTROID_02,
                SpriteInfo::ASTROID_03
        );
    }

};

#endif //BOSCONIAN_OBSTACLE_H