#ifndef BOSCONIAN_PLAYER_H
#define BOSCONIAN_PLAYER_H

#include "Entity.h"

namespace Game {

    // Player is a SubClass of Entity
    class Player : public Entity {
    private:
        int lives;
        int score;
        int currentLevel;

    public:
        Player(Utils::Vector2D pos, float deg, std::shared_ptr<Drawing::Texture> img, int lives = 3)
            : Entity(pos, deg, img, 0), lives(3), score(0), currentLevel(1)
        {}

        void setLives(int numLives) {
            lives = numLives;
        }

        int getLives() const {
            return lives;
        }

        void setScore(int playerScore) {
            score = playerScore;
        }

        int getScore() const {
            return score;
        }

        void setCurrentLevel(int level) {
            currentLevel = level;
        }

        int getCurrentLevel() const {
            return currentLevel;
        }
    };

} // Game

#endif //BOSCONIAN_PLAYER_H
