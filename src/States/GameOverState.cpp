#include "GameOverState.h"

#include "StateMachine.h"
#include "RoundStartState.h"
#include "MainMenuState.h"

void GameOverState::onEnter() {
    gameModel->reduceLives();

    if(gameModel->getLives() == 0) {
        gameModel->getGameOverAnimation()->start();
    }
}

void GameOverState::update(float deltaTime) {
    if(gameModel->getPlayer()->isDead()) {
        TextAnimation* gameOverAnimation = gameModel->getGameOverAnimation();

        gameOverAnimation->update(deltaTime);

        if (gameOverAnimation->isDone()) {

            if(gameModel->getLives() > 0) {
                gameModel->resetRound();
                StateMachine::Instance()->changeState(new RoundStartState(gameModel, gameView,
                              renderEngine, soundEngine, inputHandler));
            } else {
                StateMachine::Instance()->changeState(new MainMenuState(renderEngine, soundEngine, inputHandler));
            }

        }
    }
}

void GameOverState::render() {
    gameView->render(0);
}
