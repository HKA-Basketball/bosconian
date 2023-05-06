#ifndef BOSCONIAN_WORLD_H
#define BOSCONIAN_WORLD_H

#include "../../includes.h"
#include "../Drawing/Graphics.h"
#include "../Utilities/GlobalVars.h"

namespace Game {

    class World {
    private:
        Drawing::Graphics* g_drawing;

        unsigned long long oldTick;
        int starDelay;
        int countStars;
        float sineValue;
        bool bToggle;

        std::vector<std::pair<SDL_FRect, SDL_Color>> vcPoints;
    public:
        World(Drawing::Graphics* drawing);
        // TODO: may add x, y cuz we have an info board that may move?!
        World(Drawing::Graphics* drawing, int width, int height);

        bool initBackground();
        void runBackground(float offsetX, float offsetY);

        void draw2DRadar(Utils::Vector2D pos, Utils::Vector2D size, float offsetX, float offsetY, Utils::Vector2D mapSize);


        // TODO: add a list of Enitiys and draw it

    };

} // Game

#endif //BOSCONIAN_WORLD_H
