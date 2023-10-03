#ifndef BOSCONIAN_MAINMENUSTATE_H
#define BOSCONIAN_MAINMENUSTATE_H

#include "State.h"

class MainMenuState : public State {
public:
    void handleInput(float deltaTime) override;
    void update(float deltaTime) override;
    void render() override;
};

#endif //BOSCONIAN_MAINMENUSTATE_H
