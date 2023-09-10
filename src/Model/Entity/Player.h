#ifndef BOSCONIAN_PLAYER_H
#define BOSCONIAN_PLAYER_H

#include "SDL.h"
#include "Entity.h"
#include "Projectile.h"

class Player : public Entity {
private:
    int lives;
    int score;
    // Any other player-specific attributes...

public:
    explicit Player(SDL_Texture* texture);

    void move(int dx, int dy);   // Function to move the player.
    void shoot(Projectiles *projectiles);                // Function to make the player shoot.

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
};

#endif //BOSCONIAN_PLAYER_H
