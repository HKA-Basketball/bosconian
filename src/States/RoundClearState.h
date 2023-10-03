#ifndef BOSCONIAN_ROUNDCLEAR_H
#define BOSCONIAN_ROUNDCLEAR_H

#include "State.h"

class RoundClearState : public State {
public:
    void onEnter() override;
    void onExit() override;

    void handleInput(float deltaTime) override;
    void update(float deltaTime) override;
    void render() override;
};

#endif //BOSCONIAN_ROUNDCLEAR_H