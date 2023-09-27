#ifndef BOSCONIAN_PLAYINGSTATE_H
#define BOSCONIAN_PLAYINGSTATE_H

#include "State.h"

class PlayingState : public State {
public:
    void handleInput(float deltaTime) override;

    void update(float deltaTime) override;

    void render() override;
};

#endif //BOSCONIAN_PLAYINGSTATE_H
