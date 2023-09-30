#ifndef BOSCONIAN_MAINMENUOPTIONSTATE_H
#define BOSCONIAN_MAINMENUOPTIONSTATE_H

#include "State.h"

class MainMenuOptionState : public State {
public:
    void handleInput(float deltaTime) override;

    void update(float deltaTime) override;

    void render() override;
};

#endif //BOSCONIAN_MAINMENUOPTIONSTATE_H
