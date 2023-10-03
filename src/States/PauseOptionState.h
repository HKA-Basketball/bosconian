#ifndef BOSCONIAN_PAUSEOPTIONSTATE_H
#define BOSCONIAN_PAUSEOPTIONSTATE_H

#include "State.h"

class PauseOptionState : public State {
public:
    void onEnter() override;
    void onExit() override;

    void handleInput(float deltaTime) override;
    void update(float deltaTime) override;
    void render() override;
};

#endif //BOSCONIAN_PAUSEOPTIONSTATE_H
