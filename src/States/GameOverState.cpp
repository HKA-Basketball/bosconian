#include "GameOverState.h"

#include "StateMachine.h"
#include "RoundStartState.h"
#include "MainMenuState.h"

#include "../Model/GameModel.h"
#include "../View/GameView.h"
#include "../Controller/InputHandler.h"


void GameOverState::handleInput(float deltaTime) {
    InputHandler* inputHandler = InputHandler::Instance();
}

void GameOverState::update(float deltaTime) {
    if(GameModel::Instance()->getPlayer()->isDead()) {
        GameModel::Instance()->reduceLives();

        if(GameModel::Instance()->getLives() > 0) {
            GameModel::Instance()->resetRound();
            StateMachine::Instance()->changeState(new RoundStartState());
        } else {
            TextAnimation* gameOverAnimation = GameModel::Instance()->getGameOverAnimation();

            if (gameOverAnimation->isDone()) {
                gameOverAnimation->start();
            }

            gameOverAnimation->update(deltaTime);

            if (gameOverAnimation->isDone()) {
                StateMachine::Instance()->changeState(new MainMenuState());
            }
        }
    }
}

void GameOverState::render() {
    GameView::Instance()->render(0);
}