#include "RoundClearState.h"

#include "StateMachine.h"
#include "RoundStartState.h"

void RoundClearState::onEnter() {
    gameModel->getRoundClearAnimation()->start();
}

void RoundClearState::update(float deltaTime) {
    // Update GameState

    TextAnimation* roundClearAnimation = gameModel->getRoundClearAnimation();

    roundClearAnimation->update(deltaTime);

    if (roundClearAnimation->isDone()) {
        gameModel->nextRound();
        changedState = States::ROUND_START;
    }
}

void RoundClearState::render() {
    // Render GameStateState
    gameView->render(0);
}
