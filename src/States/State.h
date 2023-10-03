#ifndef BOSCONIAN_STATE_H
#define BOSCONIAN_STATE_H

#include <SDL.h>

class State {
public:
    virtual ~State() = default;

    virtual void onEnter() {};
    virtual void onExit() {};

    virtual void handleInput(float deltaTime) {};
    virtual void update(float deltaTime) {};
    virtual void render() {};
};

#endif //BOSCONIAN_STATE_H
