#include "EventManager.h"
#include "../Utilities/GlobalVars.h"

namespace Event {
    EventManager::EventManager() {
        mState = MouseState::Unknown;
        mButton = MouseButton::None;

        LOG(std::string("EventManager Successfully Loaded"));
    }

    bool EventManager::logging() {
        if (Utils::GlobalVars::need2ExitProc)
            return 1;

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
                    switch (event.button.button) {
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

    void EventManager::manageGameVars(float deltaTime) {
        if (!Utils::GlobalVars::dipSwitchActive && isKeyClicked(SDL_SCANCODE_ESCAPE)) {
            Utils::GlobalVars::menuActive = !Utils::GlobalVars::menuActive;
        }

        if (isKeyClicked(SDL_SCANCODE_SPACE))
        {
            if (Mix_Paused(-1))
                Mix_Resume(-1);
            else
                Mix_Pause(-1);
        }

        if (Utils::GlobalVars::menuActive)
            return;

        // TODO: Move that to the player class and handle anything related there.
        // TODO: Only change the angle ... we have a constant movement speed
        Utils::Vector2D oldPos(Utils::GlobalVars::cameraPos.x, Utils::GlobalVars::cameraPos.y);

        float movement = 200 * deltaTime;


        if (isKeyClicked(SDL_SCANCODE_LEFT, false) || isKeyClicked(SDL_SCANCODE_A, false))
            Utils::GlobalVars::cameraPos.x -= movement;
        if (isKeyClicked(SDL_SCANCODE_RIGHT, false) || isKeyClicked(SDL_SCANCODE_D, false))
            Utils::GlobalVars::cameraPos.x += movement;

        if (isKeyClicked(SDL_SCANCODE_UP, false) || isKeyClicked(SDL_SCANCODE_W, false))
            Utils::GlobalVars::cameraPos.y -= movement;
        if (isKeyClicked(SDL_SCANCODE_DOWN, false) || isKeyClicked(SDL_SCANCODE_S, false))
            Utils::GlobalVars::cameraPos.y += movement;


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
    }
} // Event