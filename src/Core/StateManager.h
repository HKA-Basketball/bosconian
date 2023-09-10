#ifndef BOSCONIAN_STATEMANAGER_H
#define BOSCONIAN_STATEMANAGER_H

#include "GameState.h"

class StateManager {
public:
    void setGameState(GameState newState) {
        currentState = newState;
    }

    GameState getGameState() const {
        return currentState;
    }

private:
    GameState currentState = GameState::MainMenu;
};


#endif //BOSCONIAN_STATEMANAGER_H
