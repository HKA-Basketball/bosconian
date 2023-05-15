#ifndef BOSCONIAN_GAME_H
#define BOSCONIAN_GAME_H

#include "../../includes.h"
#include "../Utilities/Initializer.h"
#include "Projectile.h"

namespace Game {

    class Game {
    private:
        Initialization::Initializer* g;


        std::vector<std::pair<Entity*, bool>> nonMovingEntitys;
        Entity* player1;
        std::vector<Projectile*> playersProjectiles;

    public:
        explicit Game(Initialization::Initializer *g);

        void update(float deltaTime);
        void postUpdate(float deltaTime);
        void render(float deltaTime);

        void init();
    };

} // Game

#endif //BOSCONIAN_GAME_H
