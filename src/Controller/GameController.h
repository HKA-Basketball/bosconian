#ifndef BOSCONIAN_GAMECONTROLLER_H
#define BOSCONIAN_GAMECONTROLLER_H

#include <SDL.h>
#include "InputHandler.h"
#include "../Model/GameSession.h"  // For sending input data to the game session

enum class Direction {
    UP          = 0,
    UP_RIGHT    = 45,
    RIGHT       = 90,
    DOWN_RIGHT  = 135,
    DOWN        = 180,
    DOWN_LEFT   = 225,
    LEFT        = 270,
    UP_LEFT     = 315,
    NONE        = -1,  // Useful for initial state or to represent no active movement
};

class GameController {
private:
    bool running;

    GameSession* gameSession;  // Reference to the game session to send input data
    InputHandler inputHandler;

public:
    GameController();
    void HandleInput();

    void Quit();

    bool isRunning() const {
        return this->running;
    }
};

#endif //BOSCONIAN_GAMECONTROLLER_H
