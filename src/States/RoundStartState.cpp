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
        changedState = States::PLAYING;
    }
}

void RoundStartState::render() {
    gameView->render(0);
}
