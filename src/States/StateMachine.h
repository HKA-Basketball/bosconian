
#ifndef BOSCONIAN_STATEMACHINE_H
#define BOSCONIAN_STATEMACHINE_H

#include "State.h"
#include "MainMenuState.h"
#include "PlayingState.h"
#include "../Sound/SoundEngine.h"

class StateMachine {
private:
    static StateMachine* instance;
    State* currentState;

    StateMachine(RenderEngine* renderEngine, SoundEngine* soundEngine, InputHandler* inputHandler) {
        currentState = new MainMenuState(renderEngine, soundEngine, inputHandler);
    }

    ~StateMachine() {
        delete currentState;
    }

public:

    static StateMachine* InitInstance(RenderEngine* renderEngine, SoundEngine* soundEngine, InputHandler* inputHandler) {
        if (!instance) {
            instance = new StateMachine(renderEngine, soundEngine, inputHandler);
        }
        return instance;
    }

    static StateMachine* Instance() {
        return instance;
    }

    static void DestroyInstance() {
        delete instance;
        instance = nullptr;
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
