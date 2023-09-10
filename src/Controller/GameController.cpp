#include "GameController.h"

GameController::GameController() : gameSession(nullptr) {
    this->running = true;
}

void GameController::HandleInput() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                this->Quit();
                break;
                // ... Add more SDL event handling, sending necessary commands to gameSession...
        }
    }

    // Continuous key state checks, similar to what we had in GameSession before

    const Uint8* state = SDL_GetKeyboardState(NULL);
    Direction currentDirection = Direction::NONE;

    if (state[SDL_SCANCODE_W] && state[SDL_SCANCODE_A]) {
        currentDirection = Direction::UP_LEFT;
    } else if (state[SDL_SCANCODE_W] && state[SDL_SCANCODE_D]) {
        currentDirection = Direction::UP_RIGHT;
    } else if (state[SDL_SCANCODE_S] && state[SDL_SCANCODE_A]) {
        currentDirection = Direction::DOWN_LEFT;
    } else if (state[SDL_SCANCODE_S] && state[SDL_SCANCODE_D]) {
        currentDirection = Direction::DOWN_RIGHT;
    } else if (state[SDL_SCANCODE_W]) {
        currentDirection = Direction::UP;
    } else if (state[SDL_SCANCODE_S]) {
        currentDirection = Direction::DOWN;
    } else if (state[SDL_SCANCODE_A]) {
        currentDirection = Direction::LEFT;
    } else if (state[SDL_SCANCODE_D]) {
        currentDirection = Direction::RIGHT;
    }

    // Now, based on the direction, set the player's facing direction and movement velocity.
    if (currentDirection != Direction::NONE)
        gameSession->getPlayer()->setAngle(static_cast<float>(currentDirection));

    // ... Add checks for other keys, sending commands to gameSession...
}

void GameController::Quit() {
    this->running = false;
}
