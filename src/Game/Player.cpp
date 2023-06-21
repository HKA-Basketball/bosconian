#include "Player.h"

namespace Game {

    void Player::setLives(int numLives) {
        lives = numLives;
    }

    int Player::getLives() const {
        return lives;
    }

    void Player::setScore(int playerScore) {
        score = playerScore;
    }

    int Player::getScore() const {
        return score;
    }

    void Player::setCurrentLevel(int level) {
        currentLevel = level;
    }

    int Player::getCurrentLevel() const {
        return currentLevel;
    }

    void Player::updateProjectiels(float deltaTime) {
        static Uint64 timeSinceLastProjectile = 0;
        const Uint64 projectileInterval = 250;

        if (Event::g_event->isKeyClicked(SDL_SCANCODE_LCTRL, false))
        {
            Uint64 currentTime = SDL_GetTicks64();
            if (currentTime - timeSinceLastProjectile >= projectileInterval) {
                Sound::g_sound->playSound(Sound::SOUND_SHOOT, 3, 0);
                // Add a new Projectile object to the vector
                Projectile* newProjectile1 = new Projectile(Utils::GlobalVars::cameraPos.x, Utils::GlobalVars::cameraPos.y
                        , 1000, Utils::GlobalVars::playerAngle);
                Projectile* newProjectile2 = new Projectile(Utils::GlobalVars::cameraPos.x, Utils::GlobalVars::cameraPos.y
                        , 1000, Utils::GlobalVars::playerAngle + 180);
                addProjectile(newProjectile1);
                addProjectile(newProjectile2);
                timeSinceLastProjectile = currentTime;
            }
        }
    }
} // Game