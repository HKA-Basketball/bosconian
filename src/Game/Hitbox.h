#ifndef BOSCONIAN_HITBOX_H
#define BOSCONIAN_HITBOX_H

#include "../../includes.h"

namespace Game {

    class Hitbox {
        //TODO: Idea: List of rectangles that represent the respective object(Texture) more or less.
    public:
        std::vector<SDL_Rect> hitbox;
        std::vector<SDL_Point> hitbox_Polygon;
        Utils::Vector2D pos;
        Utils::Vector2D center;

        Hitbox(const void* mem, int dataSize, Utils::Vector2D sizeOfImg);
        Hitbox(const char *file, Utils::Vector2D sizeOfImg);

        void updateHitboxPos(Utils::Vector2D pos);
        void updateHitboxAngle(float angle);
        void createHitbox(SDL_Surface* bmp, Utils::Vector2D displaySize);
        void printHitbox();

    };

} // Game

#endif //BOSCONIAN_HITBOX_H