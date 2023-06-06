#ifndef BOSCONIAN_GAME_H
#define BOSCONIAN_GAME_H

#include "../../includes.h"
#include "World.h"
#include "Projectile.h"
#include "EntityManager.h"
#include "Player.h"
#include "LevelManager.h"
#include "BaseEntity.h"
#include "LevelEditor.h"

namespace Game {

    class Game {
    private:
        EntityManager* entities;
        LevelManager lvlmgn;
        LevelEditor lvlEditor;

        std::vector<BaseEntity*> baseShipEntitys;
        Player* player1;

        std::vector<Drawing::Texture*> lives;

    public:
        explicit Game();

        ~Game() {
            for (Drawing::Texture* texture : lives) {
                delete texture;
                texture = nullptr;
            }
            lives.clear();

            // Clean up the base ship entities
            for (BaseEntity* entity : baseShipEntitys) {
                delete entity;
                entity = nullptr;
            }
            baseShipEntitys.clear();

            // Clean up the player
            delete player1;
            player1 = nullptr;

            // Clean up the entity manager
            delete entities;
            entities = nullptr;
        }

        LevelManager getLevelManager() {
            return lvlmgn;
        }

        void update(float deltaTime);
        void postUpdate(float deltaTime);
        void render(float deltaTime);

        void init();

        void HUD(std::vector<Utils::Vector2D> baseShipPos);

        void doLvlEditorStuff();
    };

} // Game

#endif //BOSCONIAN_GAME_H
