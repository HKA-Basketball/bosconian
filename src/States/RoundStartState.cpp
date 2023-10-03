#include "RoundStartState.h"

#include "StateMachine.h"
#include "PlayingState.h"

#include "../Model/GameModel.h"
#include "../View/GameView.h"

void RoundStartState::onEnter() {
    TextAnimation* readyAnimation = GameModel::Instance()->getReadyAnimation();
    readyAnimation->start();
}

void RoundStartState::update(float deltaTime) {
    TextAnimation* readyAnimation = GameModel::Instance()->getReadyAnimation();

    readyAnimation->update(deltaTime);

    if (readyAnimation->isDone()) {
        StateMachine::Instance()->changeState(new PlayingState());
    }
}

void RoundStartState::render() {
    GameView::Instance()->render(0);
}
