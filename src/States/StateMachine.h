
#ifndef BOSCONIAN_STATEMACHINE_H
#define BOSCONIAN_STATEMACHINE_H

#include "State.h"
#include "MainMenuState.h"
#include "PlayingState.h"
#include "../Sound/SoundEngine.h"

class StateMachine {
private:
    State* currentState;

public:

    StateMachine(RenderEngine* renderEngine, SoundEngine* soundEngine, InputHandler* inputHandler) {
        currentState = new MainMenuState(renderEngine, soundEngine, inputHandler);
    }

    ~StateMachine() {
        delete currentState;
    }

    void changeState(State* newState) {
        if (currentState) {
            currentState->onExit();
            delete currentState;
        }

        currentState = newState;

        if (currentState) {
            currentState->onEnter();
        }
    }

    State* getCurrentState() const { return currentState; }
};


#endif //BOSCONIAN_STATEMACHINE_H
