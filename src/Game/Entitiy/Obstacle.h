#ifndef BOSCONIAN_OBSTACLE_H
#define BOSCONIAN_OBSTACLE_H

#include "Entity.h"

namespace Game {

    class Obstacle : public Entity {
    protected:
        std::vector<std::string> images{"bomb", "astroid-01", "astroid-02", "astroid-03"};
        std::vector<int> pointsList{20, 10, 10, 10};

    public:
        Obstacle(const Utils::Vector2D& pos, float deg, const std::shared_ptr<Drawing::Texture>& img, EntityType type, Uint64 pts)
                : Entity(pos, deg, img, type, pts) {}

        Obstacle(const Utils::Vector2D& pos, float deg, const std::shared_ptr<Drawing::Texture>& img, const Utils::Vector2D& hitboxPos,
                 const Utils::Vector2D& hitboxSize, EntityType type, Uint64 pts)
                 : Entity(pos, deg, img, hitboxPos, hitboxSize, type, pts) {}

        void updateBehaviour(float deltaTime = 0.f) override {};
    };
}

#endif //BOSCONIAN_OBSTACLE_H
