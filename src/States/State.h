#ifndef BOSCONIAN_STATE_H
#define BOSCONIAN_STATE_H

#include "../Sound/SoundEngine.h"
#include "../View/RenderEngine.h"
#include "../Controller/InputHandler.h"

class State {
protected:
    RenderEngine* renderEngine;
    SoundEngine* soundEngine;
    InputHandler* inputHandler;

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
};

#endif //BOSCONIAN_STATE_H
