#include "RoundStartState.h"

#include "StateMachine.h"
#include "PlayingState.h"

void RoundStartState::onEnter() {
    gameModel->getReadyAnimation()->start();
}

void RoundStartState::update(float deltaTime) {
    TextAnimation* readyAnimation = gameModel->getReadyAnimation();

    readyAnimation->update(deltaTime);

    if (readyAnimation->isDone()) {
        StateMachine::Instance()->changeState(new PlayingState(gameModel, gameView));
    }
}

void RoundStartState::render() {
    gameView->render(0);
}
