#ifndef BOSCONIAN_STATE_H
#define BOSCONIAN_STATE_H

#include "States.h"

#include "../Sound/SoundEngine.h"
#include "../View/RenderEngine.h"
#include "../Controller/InputHandler.h"

class State {
protected:
    RenderEngine* renderEngine;
    SoundEngine* soundEngine;
    InputHandler* inputHandler;

    States changedState{States::NONE};

public:
    State(RenderEngine* renderEngine, SoundEngine* soundEngine, InputHandler* inputHandler)
        : renderEngine(renderEngine), soundEngine(soundEngine), inputHandler(inputHandler)
    {}

    virtual ~State() = default;

    virtual void onEnter() {};
    virtual void onExit() {};

    virtual void handleInput(float deltaTime) {};
    virtual void update(float deltaTime) {};
    virtual void render() {};

    States stateChanged() {
        return changedState;
    }
};

#endif //BOSCONIAN_STATE_H
