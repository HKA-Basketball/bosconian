#ifndef BOSCONIAN_GAMECONTROLLER_H
#define BOSCONIAN_GAMECONTROLLER_H

#include <SDL.h>
#include "../Model/GameSession.h"  // For sending input data to the game session

// Add this enum at the top of the file.
enum class Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT,
    UP_LEFT,
    UP_RIGHT,
    DOWN_LEFT,
    DOWN_RIGHT,
    NONE  // Useful for initial state or to represent no active movement
};

class GameController {
public:
    GameController(GameSession& session);
    void HandleInput();

private:
    GameSession& gameSession;  // Reference to the game session to send input data
};

#endif //BOSCONIAN_GAMECONTROLLER_H
