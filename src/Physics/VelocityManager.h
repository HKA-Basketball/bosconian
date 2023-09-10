#ifndef BOSCONIAN_VELOCITYMANAGER_H
#define BOSCONIAN_VELOCITYMANAGER_H
#include "../Utilities/Vec2.h"
#include "../Utilities/Degree.h"

class VelocityManager {
public:
    static void updateVelocity(Vec2& position, Degree angle, float speed, float deltaTime);
    static Vec2 getNewPosition(const Vec2& position, Degree angle, float speed, float deltaTime);

    // Other velocity-related utility functions...
};

#endif //BOSCONIAN_VELOCITYMANAGER_H
