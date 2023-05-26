#ifndef BOSCONIAN_GAME_H
#define BOSCONIAN_GAME_H

#include "../../includes.h"
#include "../Utilities/Initializer.h"
#include "Projectile.h"
#include "EntityManager.h"
#include "Player.h"
#include "LevelManager.h"

namespace Game {

    class Game {
    private:
        Initialization::Initializer* g;
        EntityManager* entities;
        LevelManager* lvlmgn;

        std::vector<Entity*> nonMovingEntitys;
        std::vector<Entity*> baseShipEntitys;
        Player* player1;
        std::vector<Projectile*> playersProjectiles;

        Entity* spyTest;

    public:
        explicit Game(Initialization::Initializer *g);

        ~Game() {
            // Clean up the non-moving entities
            for (Entity* entity : nonMovingEntitys) {
                delete entity;
            }
            nonMovingEntitys.clear();

            // Clean up the base ship entities
            for (Entity* entity : baseShipEntitys) {
                delete entity;
            }
            baseShipEntitys.clear();

            // Clean up the player
            delete player1;
            player1 = nullptr;


            delete spyTest;
            spyTest = nullptr;

            // Clean up the player projectiles
            for (Projectile* projectile : playersProjectiles) {
                delete projectile;
            }
            playersProjectiles.clear();

            // Clean up the entity manager and level manager
            delete entities;
            delete lvlmgn;
        }

        void update(float deltaTime);
        void postUpdate(float deltaTime);
        void render(float deltaTime);

        void init();
    };

} // Game

#endif //BOSCONIAN_GAME_H
