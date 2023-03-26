#include "EventManager.h"
#include "../Utilities/GlobalVars.h"

namespace Event {
    EventManager::EventManager() {
        oldTCount = SDL_GetTicks64();
        inputDelay = 50;

        mState = MouseState::Unknown;
        mButton = MouseButton::None;

        LOG(std::string("EventManager Successfully Loaded"));
    }

    bool EventManager::startLogging() {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    // Handle window close event
                    return 1;
                    break;
                case SDL_KEYDOWN:
                case SDL_KEYUP:
                    // Handle key event
                    kState[event.key.keysym.scancode] = event.type == SDL_KEYDOWN ? KeyboardState::KeyDown : KeyboardState::KeyUp;
                case SDL_MOUSEBUTTONDOWN:
                case SDL_MOUSEBUTTONUP:
                    // Handle mouse button event
                    switch (event.key.keysym.scancode) {
                        case SDL_BUTTON_LEFT:
                            mState = event.type == SDL_MOUSEBUTTONDOWN ? MouseState::Down : MouseState::Up;
                            mButton = MouseButton::Left;
                            break;
                        case SDL_BUTTON_RIGHT:
                            mState = event.type == SDL_MOUSEBUTTONDOWN ? MouseState::Down : MouseState::Up;
                            mButton = MouseButton::Right;
                            break;
                        default:
                            break;
                    }
                    // Add cases for other types of events as needed
            }
        }

        return 0;
    }

    void EventManager::manageGameVars() {
        if (isKeyClicked(SDL_SCANCODE_SPACE))
        {
            if (Mix_Paused(-1))
                Mix_Resume(-1);
            else
                Mix_Pause(-1);
        }

        if (SDL_GetTicks64() - oldTCount < inputDelay)
            return;

        // TODO: Move that to the player class and handle anything related there.
        Utils::Vector2D oldPos(Utils::GlobalVars::playerPos.x, Utils::GlobalVars::playerPos.y);

        if (kState[SDL_SCANCODE_LEFT] == KeyboardState::KeyDown || kState[SDL_SCANCODE_A] == KeyboardState::KeyDown)
            Utils::GlobalVars::playerPos.x -= 10;
        if (kState[SDL_SCANCODE_RIGHT] == KeyboardState::KeyDown || kState[SDL_SCANCODE_D] == KeyboardState::KeyDown)
            Utils::GlobalVars::playerPos.x += 10;

        if (kState[SDL_SCANCODE_UP] == KeyboardState::KeyDown || kState[SDL_SCANCODE_W] == KeyboardState::KeyDown)
            Utils::GlobalVars::playerPos.y -= 10;
        if (kState[SDL_SCANCODE_DOWN] == KeyboardState::KeyDown || kState[SDL_SCANCODE_S] == KeyboardState::KeyDown)
            Utils::GlobalVars::playerPos.y += 10;


        if (Utils::GlobalVars::playerPos.x < oldPos.x) // Left
            Utils::GlobalVars::playerAngle = -90.f;
        else if (Utils::GlobalVars::playerPos.x > oldPos.x) // Right
            Utils::GlobalVars::playerAngle = 90.f;
        else if (Utils::GlobalVars::playerPos.y > oldPos.y) // Down
            Utils::GlobalVars::playerAngle = 180.f;
        else if (Utils::GlobalVars::playerPos.y < oldPos.y) // Up
            Utils::GlobalVars::playerAngle = 0.f;

        if (Utils::GlobalVars::playerPos.x < oldPos.x && Utils::GlobalVars::playerPos.y < oldPos.y) // Left Up
            Utils::GlobalVars::playerAngle = -45.f;
        else if (Utils::GlobalVars::playerPos.x > oldPos.x && Utils::GlobalVars::playerPos.y < oldPos.y) // Right Up
            Utils::GlobalVars::playerAngle = 45.f;
        else if (Utils::GlobalVars::playerPos.x < oldPos.x && Utils::GlobalVars::playerPos.y > oldPos.y) // Left Down
            Utils::GlobalVars::playerAngle = -135.f;
        else if (Utils::GlobalVars::playerPos.x > oldPos.x && Utils::GlobalVars::playerPos.y > oldPos.y) // Right Down
            Utils::GlobalVars::playerAngle = 135.f;


        if ((Utils::GlobalVars::playerPos.x < 0))
        {
            Utils::GlobalVars::playerPos.x = Utils::GlobalVars::lvlWidth;
            Utils::GlobalVars::playerAngle = -90.f;
        }

        if ((Utils::GlobalVars::playerPos.x > Utils::GlobalVars::lvlWidth))
        {
            Utils::GlobalVars::playerPos.x = 0;
            Utils::GlobalVars::playerAngle = 90.f;
        }

        if ((Utils::GlobalVars::playerPos.y < 0))
        {
            Utils::GlobalVars::playerPos.y = Utils::GlobalVars::lvlHeight;
            Utils::GlobalVars::playerAngle = 0.f;
        }

        if ((Utils::GlobalVars::playerPos.y > Utils::GlobalVars::lvlHeight))
        {
            Utils::GlobalVars::playerPos.y = 0;
            Utils::GlobalVars::playerAngle = 180.f;
        }

        oldTCount = SDL_GetTicks64();
    }
} // Event