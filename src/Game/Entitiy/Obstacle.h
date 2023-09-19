#ifndef BOSCONIAN_OBSTACLE_H
#define BOSCONIAN_OBSTACLE_H

#include "Entity.h"

namespace Game {

    class Obstacle : public Entity {
    public:
        Obstacle(Utils::Vector2D pos, float deg, std::shared_ptr<Drawing::Texture> img, EntityType type, Uint64 pts)
                : Entity(pos, deg, img, type, pts) {}

        Obstacle(Utils::Vector2D pos, float deg, std::shared_ptr<Drawing::Texture> img, Utils::Vector2D hitboxPos,
                 Utils::Vector2D hitboxSize, EntityType type, Uint64 pts)
                 : Entity(pos, deg, img, hitboxPos, hitboxSize, type, pts) {}

        void updateBehaviour(float deltaTime = 0.f) override {};
    };
}

#endif //BOSCONIAN_OBSTACLE_H
