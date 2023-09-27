
#ifndef BOSCONIAN_STATEMACHINE_H
#define BOSCONIAN_STATEMACHINE_H

#include "State.h"
#include "MainMenuState.h"
#include "PlayingState.h"

class StateMachine {
private:
    static StateMachine* instance;
    State* currentState;

    StateMachine() : currentState(new MainMenuState()) {} /*TODO Change to MainMenuState/Intro */
    ~StateMachine() { delete currentState; }

public:
    static StateMachine* Instance() {
        if (!instance) {
            instance = new StateMachine();
        }
        return instance;
    }

    static void DestroyInstance() {
        delete instance;
        instance = nullptr;
    }

    void changeState(State* state) {
        delete currentState;
        currentState = state;
    }

    State* getCurrentState() const { return currentState; }
};


#endif //BOSCONIAN_STATEMACHINE_H
