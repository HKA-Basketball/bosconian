#ifndef BOSCONIAN_STATE_H
#define BOSCONIAN_STATE_H

#include <SDL.h>

class State {
public:
    virtual ~State() = default;
    virtual void handleInput(float deltaTime) = 0;
    virtual void update(float deltaTime) = 0;
    virtual void render() = 0;
};

#endif //BOSCONIAN_STATE_H
