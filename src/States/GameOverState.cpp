#include "GameOverState.h"

#include "StateMachine.h"
#include "RoundStartState.h"
#include "MainMenuState.h"

#include "../Model/GameModel.h"
#include "../View/GameView.h"
#include "../Controller/InputHandler.h"

void GameOverState::onEnter() {
    GameModel::Instance()->reduceLives();

    if(GameModel::Instance()->getLives() == 0) {
        TextAnimation* gameOverAnimation = GameModel::Instance()->getGameOverAnimation();
        gameOverAnimation->start();
    }
}

void GameOverState::handleInput(float deltaTime) {
    InputHandler* inputHandler = InputHandler::Instance();
}

void GameOverState::update(float deltaTime) {
    if(GameModel::Instance()->getPlayer()->isDead()) {
        TextAnimation* gameOverAnimation = GameModel::Instance()->getGameOverAnimation();

        gameOverAnimation->update(deltaTime);

        if (gameOverAnimation->isDone()) {

            if(GameModel::Instance()->getLives() > 0) {
                GameModel::Instance()->resetRound();
                StateMachine::Instance()->changeState(new RoundStartState());
            } else {
                StateMachine::Instance()->changeState(new MainMenuState());
            }

        }
    }
}

void GameOverState::render() {
    GameView::Instance()->render(0);
}
