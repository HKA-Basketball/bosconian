#ifndef BOSCONIAN_PHYSICSSTATE_H
#define BOSCONIAN_PHYSICSSTATE_H

#include "../Utilities/Vec2.h"
#include "../Utilities/Degree.h"

struct PhysicsState {
    Vec2 position;
    float speed;
    Degree angle;
};

#endif //BOSCONIAN_PHYSICSSTATE_H
