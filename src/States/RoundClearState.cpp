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
        StateMachine::Instance()->changeState(new RoundStartState(gameModel, gameView,
                      renderEngine, soundEngine, inputHandler));
    }
}

void RoundClearState::render() {
    // Render GameStateState
    gameView->render(0);
}
