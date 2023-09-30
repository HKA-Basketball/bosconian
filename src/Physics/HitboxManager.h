#ifndef BOSCONIAN_HITBOXMANAGER_H
#define BOSCONIAN_HITBOXMANAGER_H

#include "Hitbox.h"

class HitboxManager {
public:
    /**
     * @brief Checks if two hitboxes are colliding.
     *
     * @param box1 The first hitbox.
     * @param box2 The second hitbox.
     * @return true if the hitboxes are colliding, false otherwise.
     */
    static bool areColliding(const Hitbox& box1, const Hitbox& box2);

private:
    static float projectOntoAxis(const Hitbox& box, const Vector2D& axis);

};

#endif //BOSCONIAN_HITBOXMANAGER_H
