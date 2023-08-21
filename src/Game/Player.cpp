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

    void Player::updateProjectiles(float deltaTime) {
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

    void Player::updateMovement(float deltaTime) {
        Utils::Vector2D oldPos(Utils::GlobalVars::cameraPos.x, Utils::GlobalVars::cameraPos.y);

        float movement = 200 * deltaTime;

        if (Utils::GlobalVars::lvlEditorActive && Event::g_event->isKeyClicked(SDL_SCANCODE_LSHIFT, false))
            movement = 10 * deltaTime;

        static float moveX = 0.0f;  // Horizontal movement
        static float moveY = -1.0f; // Vertical movement
        static float oldMoveX = 0.0f;
        static float oldMoveY = -1.0f;

        if (Event::g_event->isKeyClicked(SDL_SCANCODE_LEFT, false) || Event::g_event->isKeyClicked(SDL_SCANCODE_A, false)) {
            moveX = -1.0f;
        }
        else if (Event::g_event->isKeyClicked(SDL_SCANCODE_RIGHT, false) || Event::g_event->isKeyClicked(SDL_SCANCODE_D, false)) {
            moveX = 1.0f;
        }

        if (Event::g_event->isKeyClicked(SDL_SCANCODE_UP, false) || Event::g_event->isKeyClicked(SDL_SCANCODE_W, false)) {
            moveY = -1.0f;
        }
        else if (Event::g_event->isKeyClicked(SDL_SCANCODE_DOWN, false) || Event::g_event->isKeyClicked(SDL_SCANCODE_S, false)) {
            moveY = 1.0f;
        }

        if (!Utils::GlobalVars::lvlEditorActive && moveX == 0 && moveY == 0)
        {
            moveX = oldMoveX;
            moveY = oldMoveY;
        }

        Utils::GlobalVars::cameraPos.x += moveX * movement;
        Utils::GlobalVars::cameraPos.y += moveY * movement;
        oldMoveX = moveX;
        oldMoveY = moveY;
        moveX = 0.f;
        moveY = 0.f;

        if (Utils::GlobalVars::cameraPos.x < oldPos.x) // Left
            Utils::GlobalVars::playerAngle = -90.f;
        else if (Utils::GlobalVars::cameraPos.x > oldPos.x) // Right
            Utils::GlobalVars::playerAngle = 90.f;
        else if (Utils::GlobalVars::cameraPos.y > oldPos.y) // Down
            Utils::GlobalVars::playerAngle = 180.f;
        else if (Utils::GlobalVars::cameraPos.y < oldPos.y) // Up
            Utils::GlobalVars::playerAngle = 0.f;

        if (Utils::GlobalVars::cameraPos.x < oldPos.x && Utils::GlobalVars::cameraPos.y < oldPos.y) // Left Up
            Utils::GlobalVars::playerAngle = -45.f;
        else if (Utils::GlobalVars::cameraPos.x > oldPos.x && Utils::GlobalVars::cameraPos.y < oldPos.y) // Right Up
            Utils::GlobalVars::playerAngle = 45.f;
        else if (Utils::GlobalVars::cameraPos.x < oldPos.x && Utils::GlobalVars::cameraPos.y > oldPos.y) // Left Down
            Utils::GlobalVars::playerAngle = -135.f;
        else if (Utils::GlobalVars::cameraPos.x > oldPos.x && Utils::GlobalVars::cameraPos.y > oldPos.y) // Right Down
            Utils::GlobalVars::playerAngle = 135.f;

        if ((Utils::GlobalVars::cameraPos.x < 0))
            Utils::GlobalVars::cameraPos.x += Utils::GlobalVars::lvlWidth;

        if ((Utils::GlobalVars::cameraPos.x > Utils::GlobalVars::lvlWidth))
            Utils::GlobalVars::cameraPos.x -= Utils::GlobalVars::lvlWidth;

        if ((Utils::GlobalVars::cameraPos.y < 0))
            Utils::GlobalVars::cameraPos.y += Utils::GlobalVars::lvlHeight;

        if ((Utils::GlobalVars::cameraPos.y > Utils::GlobalVars::lvlHeight))
            Utils::GlobalVars::cameraPos.y -= Utils::GlobalVars::lvlHeight;


        this->setOrigin(Utils::GlobalVars::cameraPos);
        this->setAngle(Utils::GlobalVars::playerAngle);
    }

} // Game