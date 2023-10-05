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
                SpriteInfo::ASTEROID_01,
                SpriteInfo::ASTEROID_02,
                SpriteInfo::ASTEROID_03
        );

        hitbox = {position, {
                static_cast<float>(spriteMap.at(spriteInfo).w),
                static_cast<float>(spriteMap.at(spriteInfo).h)}
        };

        switch (spriteInfo) {
            default:
                points = 10;
                break;
            case SpriteInfo::BOMB:
                points = 20;
                break;
        }

    }

};

#endif //BOSCONIAN_OBSTACLE_H
