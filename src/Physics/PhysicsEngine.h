#ifndef BOSCONIAN_PHYSICSENGINE_H
#define BOSCONIAN_PHYSICSENGINE_H

#include "../Model/Entity/Entity.h"
#include <vector>

class PhysicsEngine {
public:
    bool checkOBBCollision(const Entity& a, const Entity& b);
    void resolveCollisions(std::vector<Entity>& entities);
};

#endif //BOSCONIAN_PHYSICSENGINE_H
