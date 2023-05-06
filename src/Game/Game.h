#ifndef BOSCONIAN_GAME_H
#define BOSCONIAN_GAME_H

#include "../../includes.h"
#include "../Utilities/Initializer.h"

namespace Game {

    class Game {
    private:
        Initialization::Initializer* g;


        std::vector<std::pair<Entity*, Drawing::Image*>> nonMovingEntitys;
        Entity* player1;

    public:
        explicit Game(Initialization::Initializer *g);

        void playTest();

        void initOnce();
    };

} // Game

#endif //BOSCONIAN_GAME_H
