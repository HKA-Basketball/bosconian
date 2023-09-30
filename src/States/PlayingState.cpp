#include "PlayingState.h"

#include <iostream>

#include "PauseState.h"
#include "GameOverState.h"
#include "StateMachine.h"
#include "../Model/GameModel.h"
#include "../View/GameView.h"
#include "../Controller/InputHandler.h"

void PlayingState::handleInput(float deltaTime) {

    InputHandler* inputHandler = InputHandler::Instance();

    float angle = -1; // Initialize to an invalid angle
    if (inputHandler->isKeyPressed(SDLK_w) && inputHandler->isKeyPressed(SDLK_a)) {
        angle = 315; // up-left
    } else if (inputHandler->isKeyPressed(SDLK_w) && inputHandler->isKeyPressed(SDLK_d)) {
        angle = 45; // up-right
    } else if (inputHandler->isKeyPressed(SDLK_s) && inputHandler->isKeyPressed(SDLK_a)) {
        angle = 225; // down-left
    } else if (inputHandler->isKeyPressed(SDLK_s) && inputHandler->isKeyPressed(SDLK_d)) {
        angle = 135; // down-right
    } else if (inputHandler->isKeyPressed(SDLK_w)) {
        angle = 0; // up
    } else if (inputHandler->isKeyPressed(SDLK_s)) {
        angle = 180; // down
    } else if (inputHandler->isKeyPressed(SDLK_a)) {
        angle = 270; // left
    } else if (inputHandler->isKeyPressed(SDLK_d)) {
        angle = 90; // right
    }

    if (angle != -1) {
        GameModel::Instance()->getPlayer()->setAngle(angle);
    }

    if (inputHandler->isKeyPressed(SDLK_LCTRL)) {
        GameModel::Instance()->getPlayer()->shoot(deltaTime);
    }

    if (inputHandler->isKeyPressed(SDLK_k)) {
        GameModel::Instance()->getPlayer()->setDefeated();
    }

    if (inputHandler->isKeyPressedAndErase(SDLK_ESCAPE)) {
        StateMachine::Instance()->changeState(new PauseState());
    }
}

void PlayingState::update(float deltaTime) {
    // Update GameState
    GameModel::Instance()->update(deltaTime);

    Player* player = GameModel::Instance()->getPlayer();

    if(player->isDefeated()) {
        StateMachine::Instance()->changeState(new GameOverState());
    }
}

void PlayingState::render() {
    // Render GameStateState
    GameView::Instance()->render(0);
}