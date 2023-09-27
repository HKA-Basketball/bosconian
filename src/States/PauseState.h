#ifndef BOSCONIAN_PAUSESTATE_H
#define BOSCONIAN_PAUSESTATE_H

#include "State.h"

class PauseState : public State {
public:
    void handleInput(float deltaTime) override;

    void update(float deltaTime) override;

    void render() override;
};

#endif //BOSCONIAN_PAUSESTATE_H
