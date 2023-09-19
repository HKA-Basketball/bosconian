#ifndef BOSCONIAN_GAME_H
#define BOSCONIAN_GAME_H

#include "../../includes.h"
#include "World.h"
#include "Projectile.h"
#include "Entitiy/EntityManager.h"
#include "Entitiy/Player.h"
#include "LevelManager.h"
#include "Entitiy/BaseEntity.h"
#include "LevelEditor.h"

namespace Game {

    /**
     * The Game class manages the main gameplay loop, entities, and levels in the game.
     */
    class Game {
    private:
        EntityManager* entities;
        LevelManager lvlmgn;
        LevelEditor lvlEditor;

        /** Collection of base ship entities in the game. */
        std::vector<BaseEntity*> baseShipEntitys;
        /** Pointer to the player entity in the game. */
        Player* player1;

        /** Collection of textures representing player lives. */
        std::vector<Drawing::Texture*> lives;

        Utils::Config sw_cfg = Utils::Config(".\\cfg\\score.ini");

    public:
        /**
         * Default constructor for the Game class.
         */
        explicit Game();

        /**
         * Destructor for the Game class.
         * Cleans up memory used by game entities, textures, and instances.
         */
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

        /**
         * Get the LevelManager instance for managing game levels.
         * \return The LevelManager instance.
         */
        LevelManager getLevelManager() {
            return lvlmgn;
        }

        /**
         * Update game logic based on elapsed time.
         * \param deltaTime The time elapsed since the last update in seconds.
         */
        void update(float deltaTime);

        /**
         * Perform post-update actions and game logic based on elapsed time.
         * \param deltaTime The time elapsed since the last update in seconds.
         */
        void postUpdate(float deltaTime);

        /**
         * Render game entities and components based on elapsed time.
         * \param deltaTime The time elapsed since the last render in seconds.
         */
        void render(float deltaTime);

        /**
         * Initialize the game and its components.
         */
        void init();

        /**
         * Display the heads-up display (HUD) based on base ship positions.
         * \param baseShipPos A vector of base ship positions.
         */
        void HUD(std::vector<Utils::Vector2D> baseShipPos);

        /**
         * Perform actions related to the level editor.
         */
        void doLvlEditorStuff();

        static void updateScore(Entity *entity);

        bool checkEntityCollisions(Entity *entity);

        EntityManager *getEntities() const;

        const std::vector<BaseEntity *> &getBaseShipEntities() const;

        Player *getPlayer1() const;
    };

} // Game

#endif //BOSCONIAN_GAME_H
