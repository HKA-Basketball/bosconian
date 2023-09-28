#ifndef BOSCONIAN_WORLD_H
#define BOSCONIAN_WORLD_H

#include "../Utilities/Vector2D.h"
#include "../Utilities/Config.h"

class World {
public:
    constexpr static const float WIDTH = Config::levelWidth;  // width of the world
    constexpr static const float HEIGHT = Config::levelHeight; // height of the world

    // Wrap a position around the world boundaries
    static Vector2D WrapPosition(const Vector2D& position) {
        float wrappedX = std::fmod(std::fmod(position.x, WIDTH) + WIDTH, WIDTH);
        float wrappedY = std::fmod(std::fmod(position.y, HEIGHT) + HEIGHT, HEIGHT);
        return {wrappedX, wrappedY};
    }
};

#endif //BOSCONIAN_WORLD_H
