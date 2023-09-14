#ifndef BOSCONIAN_PLAYER_H
#define BOSCONIAN_PLAYER_H

#include "Entity.h"
#include "../../Event/EventManager.h"
#include "../../Sound/SoundManager.h"

namespace Game {

    /**
     * The Player class represents the player's character in the game.
     */
    class Player : public Entity {
    private:
        int lives;
        int score;
        int currentLevel;
        int currentCondition;

        bool dead;

    public:
        /**
         * Constructs a Player instance with the specified position, rotation, texture, and initial lives.
         * \param pos The initial position of the player as a Vector2D.
         * \param deg The initial rotation angle of the player in degrees.
         * \param img The texture of the player as a shared_ptr to Texture.
         * \param lives The initial number of lives for the player (default is 3).
         */
        Player(Utils::Vector2D pos, float deg, std::shared_ptr<Drawing::Texture> img, int lives = 3)
            : Entity(pos, deg, img, EntityType::Player, 0), lives(3), score(0), currentLevel(1)
        {}

        /**
         * Sets the number of lives for the player.
         * \param numLives The new number of lives.
         */
        void setLives(int numLives);

        /**
         * Gets the current number of lives for the player.
         * \return The current number of lives.
         */
        int getLives() const;

        /**
         * Sets the player's score.
         * \param playerScore The new score for the player.
         */
        void setScore(int playerScore);

        /**
         * Gets the player's current score.
         * \return The current score.
         */
        int getScore() const;

        /**
         * Sets the player's current level.
         * \param level The new level for the player.
         */
        void setCurrentLevel(int level);

        /**
         * Gets the player's current level.
         * \return The current level.
         */
        int getCurrentLevel() const;

        void setDead(bool playerDead);

        bool isDead() const;

        /**
         * Updates the player's projectiles based on the specified delta time.
         * \param deltaTime The time elapsed since the last update.
         */
        void updateProjectiles(float deltaTime);

        /**
         * Updates the player's movement based on the specified delta time.
         * \param deltaTime The time elapsed since the last update.
         */
        void updateMovement(float deltaTime);
    };

} // Game

#endif //BOSCONIAN_PLAYER_H
