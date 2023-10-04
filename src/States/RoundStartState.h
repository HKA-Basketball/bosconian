#ifndef BOSCONIAN_ROUNDSTARTSTATE_H
#define BOSCONIAN_ROUNDSTARTSTATE_H

#include "State.h"

#include "../Model/GameModel.h"
#include "../View/GameView.h"
#include "../Controller/InputHandler.h"

class RoundStartState : public State {
    GameModel* gameModel;
    GameView* gameView;

public:

    RoundStartState(GameModel* gameModel, GameView* gameView,
            RenderEngine* renderEngine, SoundEngine* soundEngine, InputHandler* inputHandler)
            : State(renderEngine, soundEngine, inputHandler), gameModel(gameModel), gameView(gameView) {};

    ~RoundStartState() {}

    void onEnter() override;

    void update(float deltaTime) override;
    void render() override;
};

#endif //BOSCONIAN_ROUNDSTARTSTATE_H
