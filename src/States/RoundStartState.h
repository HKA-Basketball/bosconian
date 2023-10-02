#ifndef BOSCONIAN_ROUNDSTARTSTATE_H
#define BOSCONIAN_ROUNDSTARTSTATE_H

#include "State.h"

class RoundStartState : public State {
public:
    void onEnter() override;
    void onExit() override;

    void handleInput(float deltaTime) override;
    void update(float deltaTime) override;
    void render() override;
};

#endif //BOSCONIAN_ROUNDSTARTSTATE_H
