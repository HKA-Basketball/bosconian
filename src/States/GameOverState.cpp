#include "GameOverState.h"

#include "../Model/GameModel.h"
#include "../View/GameView.h"
#include "../Controller/InputHandler.h"

void GameOverState::handleInput(float deltaTime) {
    InputHandler* inputHandler = InputHandler::Instance();
}

void GameOverState::update(float deltaTime) {
    GameModel::Instance()->update(deltaTime);

    if(GameModel::Instance()->getPlayer()->isDead()) {
        GameModel::Instance()->reduceLives();

        if(GameModel::Instance()->getLives() > 0) {
            GameModel::Instance()->getPlayer()->reset();
            StateMachine::Instance()->changeState(new PlayingState());
        } else {
            StateMachine::Instance()->changeState(new MainMenuState());
        }
    }
}

void GameOverState::render() {
    GameView::Instance()->render(0);
}