#ifndef BOSCONIAN_WORLD_H
#define BOSCONIAN_WORLD_H

#include "../Utilities/Vector2D.h"
#include "../Utilities/Config.h"

class World {
public:
    static const int WIDTH = Config::levelWidth;  // width of the world
    static const int HEIGHT = Config::levelHeight; // height of the world

    // Wrap a position around the world boundaries
    static Vector2D WrapPosition(const Vector2D& position) {
        float wrappedX = std::fmod(position.x, WIDTH);
        float wrappedY = std::fmod(position.y, HEIGHT);
        return Vector2D(wrappedX, wrappedY);
    }
};

#endif //BOSCONIAN_WORLD_H
