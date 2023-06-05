#ifndef BOSCONIAN_GAME_H
#define BOSCONIAN_GAME_H

#include "../../includes.h"
#include "../Utilities/Initializer.h"
#include "Projectile.h"
#include "EntityManager.h"
#include "Player.h"
#include "LevelManager.h"
#include "BaseEntity.h"

namespace Game {

    class Game {
    private:
        Initialization::Initializer* g;
        //EntityManager* entities;
        LevelManager* lvlmgn;

        std::vector<Entity*> nonMovingEntitys;
        std::vector<BaseEntity*> baseShipEntitys;
        Player* player1;
        std::vector<Projectile*> playersProjectiles;

        std::vector<Drawing::Texture*> lives;

    public:
        explicit Game(Initialization::Initializer *g);

        ~Game() {
            // Clean up the non-moving entities
            for (Entity* entity : nonMovingEntitys) {
                delete entity;
            }
            nonMovingEntitys.clear();

            for (Drawing::Texture* texture : lives) {
                delete texture;
            }
            lives.clear();

            // Clean up the base ship entities
            for (BaseEntity* entity : baseShipEntitys) {
                delete entity;
            }
            baseShipEntitys.clear();

            // Clean up the player
            delete player1;
            player1 = nullptr;

            // Clean up the player projectiles
            for (Projectile* projectile : playersProjectiles) {
                delete projectile;
            }
            playersProjectiles.clear();

            // Clean up the entity manager and level manager
            //delete entities;
            //entities = nullptr;
            delete lvlmgn;
            lvlmgn = nullptr;
        }

        void update(float deltaTime);
        void postUpdate(float deltaTime);
        void render(float deltaTime);

        void init();

        void HUD(std::vector<Utils::Vector2D> baseShipPos);
    };

} // Game

#endif //BOSCONIAN_GAME_H
