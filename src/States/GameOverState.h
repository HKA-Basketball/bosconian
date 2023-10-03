#ifndef BOSCONIAN_GAMEOVERSTATE_H
#define BOSCONIAN_GAMEOVERSTATE_H

#include "State.h"

class GameOverState : public State {
public:
    void onEnter() override;

    void handleInput(float deltaTime) override;
    void update(float deltaTime) override;
    void render() override;
};

#endif //BOSCONIAN_GAMEOVERSTATE_H
