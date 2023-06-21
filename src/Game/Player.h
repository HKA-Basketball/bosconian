#ifndef BOSCONIAN_PLAYER_H
#define BOSCONIAN_PLAYER_H

#include "Entity.h"
#include "../Event/EventManager.h"
#include "../Sound/SoundManager.h"

namespace Game {

    // Player is a SubClass of Entity
    class Player : public Entity {
    private:
        int lives;
        int score;
        int currentLevel;
        int currentCondition;

    public:
        Player(Utils::Vector2D pos, float deg, std::shared_ptr<Drawing::Texture> img, int lives = 3)
            : Entity(pos, deg, img, EntityType::Player, 0), lives(3), score(0), currentLevel(1)
        {}

        void setLives(int numLives);

        int getLives() const;

        void setScore(int playerScore);

        int getScore() const;

        void setCurrentLevel(int level);

        int getCurrentLevel() const;

        void updateProjectiels(float deltaTime);
    };

} // Game

#endif //BOSCONIAN_PLAYER_H
