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
                changedState = States::ROUND_START;
            } else {
                changedState = States::MAIN_MENU;
            }

        }
    }
}

void GameOverState::render() {
    gameView->render(0);
}
