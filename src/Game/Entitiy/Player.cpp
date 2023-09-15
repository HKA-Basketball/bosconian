#include "Player.h"

namespace Game {

    void Player::updateProjectiles(float deltaTime) {
        static Uint64 timeSinceLastProjectile = 0;
        const Uint64 projectileInterval = 250;

        if (Event::g_event->isKeyClicked(SDL_SCANCODE_LCTRL, false))
        {
            Uint64 currentTime = SDL_GetTicks64();
            if (currentTime - timeSinceLastProjectile >= projectileInterval) {
                Sound::g_sound->playSound(Sound::SOUND_SHOOT, 3, 0);

                auto x = static_cast<int>(Utils::GlobalVars::cameraPos.x);
                auto y = static_cast<int>(Utils::GlobalVars::cameraPos.y);
                auto angle = Utils::GlobalVars::playerAngle;

                addProjectile(new Projectile(x, y, 1000, angle));
                addProjectile(new Projectile(x, y, 1000, angle + 180));

                timeSinceLastProjectile = currentTime;
            }
        }
    }

    void Player::updateMovement(float deltaTime) {
        auto oldPos = Utils::GlobalVars::cameraPos;

        float movement = Utils::GlobalVars::lvlEditorActive && Event::g_event->isKeyClicked(SDL_SCANCODE_LSHIFT, false)
                ? 10 * deltaTime : 200 * deltaTime;


        static float moveX = 0.0f;
        static float moveY = -1.0f;
        static float oldMoveX = 0.0f;
        static float oldMoveY = -1.0f;

        auto updateMoveDirection = [](float& move, SDL_Scancode positiveKey, SDL_Scancode negativeKey) {
            if (Event::g_event->isKeyClicked(positiveKey, false)) move = 1.0f;
            else if (Event::g_event->isKeyClicked(negativeKey, false)) move = -1.0f;
            else move = 0.f;
        };

        updateMoveDirection(moveX, SDL_SCANCODE_RIGHT, SDL_SCANCODE_LEFT);
        updateMoveDirection(moveX, SDL_SCANCODE_D, SDL_SCANCODE_A);
        updateMoveDirection(moveY, SDL_SCANCODE_DOWN, SDL_SCANCODE_UP);
        updateMoveDirection(moveY, SDL_SCANCODE_S, SDL_SCANCODE_W);

        if (!Utils::GlobalVars::lvlEditorActive && moveX == 0 && moveY == 0) {
            moveX = oldMoveX;
            moveY = oldMoveY;
        }

        Utils::GlobalVars::cameraPos.x += moveX * movement;
        Utils::GlobalVars::cameraPos.y += moveY * movement;

        float& x = Utils::GlobalVars::cameraPos.x;
        float& y = Utils::GlobalVars::cameraPos.y;
        const float& oldX = oldPos.x;
        const float& oldY = oldPos.y;
        float& angle = Utils::GlobalVars::playerAngle;
        const float& lvlWidth = static_cast<float>(Utils::GlobalVars::lvlWidth);
        const float& lvlHeight = static_cast<float>(Utils::GlobalVars::lvlHeight);

        bool movedLeft = x < oldX;
        bool movedRight = x > oldX;
        bool movedUp = y < oldY;
        bool movedDown = y > oldY;

        if (movedLeft && movedUp) angle = -45.f;
        else if (movedRight && movedUp) angle = 45.f;
        else if (movedLeft && movedDown) angle = -135.f;
        else if (movedRight && movedDown) angle = 135.f;
        else if (movedLeft) angle = -90.f;
        else if (movedRight) angle = 90.f;
        else if (movedDown) angle = 180.f;
        else if (movedUp) angle = 0.f;

        x = std::fmod(x + lvlWidth, lvlWidth);
        y = std::fmod(y + lvlHeight, lvlHeight);


        oldMoveX = moveX;
        oldMoveY = moveY;

        this->setOrigin(Utils::GlobalVars::cameraPos);
        this->setAngle(Utils::GlobalVars::playerAngle);
    }

} // namespace Game