#ifndef BOSCONIAN_ROUNDSTARTSTATE_H
#define BOSCONIAN_ROUNDSTARTSTATE_H

#include "State.h"

#include "../Model/GameModel.h"
#include "../View/GameView.h"

class RoundStartState : public State {
    GameModel* gameModel;
    GameView* gameView;

public:
    RoundStartState() : RoundStartState(GameModel::Instance(), GameView::Instance()) {};

    RoundStartState(GameModel* gameModel, GameView* gameView) : gameModel(gameModel), gameView(gameView) {};

    ~RoundStartState() {}

    void onEnter() override;

    void update(float deltaTime) override;
    void render() override;
};

#endif //BOSCONIAN_ROUNDSTARTSTATE_H
