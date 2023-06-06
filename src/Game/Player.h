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

        void updateProjectiels(float deltaTime) {
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
    };

} // Game

#endif //BOSCONIAN_PLAYER_H
